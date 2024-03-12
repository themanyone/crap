#if 0
crap "$0" |tcc -Iinclude -Llib -lreg -run - "$@";exit $?
#endif
/* Concise, Regex-Aware Preprocessor (CRAP)
C (computer language) code decorator and language maker

Copyright (C) 2018-2024 Henry Kroll III, https://thenerdshow.com

Permission to use, copy, modify, distribute, and sell this software and
its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice appears in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, including About boxes in derived user
interfaces or web front-ends. No redpresentations are made about the
suitability of this software for any purpose. It is provided "as is"
without express or implied warranty.
*/
#include "crap.h"
#include "sjoin.h"
#include "print.h"

#define INDENT while(indent > prev_indent){  \
    *s = prepend(*s, "{") , prev_indent += TAB;}
struct{
    char to[10], end[5];}
skip = {{'\0'}, {'\2'}};
char *has_main=NULL, eol[255]={'\0'};
struct macro *maclist = NULL;
int prev_indent = 0, indent = 0;
void macros(char **s){
    char *tmp, *match, *changed;
    {// if done skipping over comments, triple-quotes
        // put keyword macros here
        // main becomes int main()
        if (!(has_main || strcmp(*s, "main"))){
            has_main = strcpy(*s, "int main(int argc, char **argv, char **env)");}
        int max;
        #define SUB(match, rep)                     \
        max = MAX_REPLACE;                           \
        while(max-- && (tmp=resub(*s, match, rep))){ \
            strcpy(*s, tmp) ;free(tmp);}
        // array[:] notation now works most places (do not free)
        // this one employs a non-standard GNU extension
        SUB("([(*,=]\\s*|  )([^[\" ]+)\\s*\\[(\\w*):(\\w*)\\]([[);, ]+|$)",
          "\1({typeof(\2) tmp = {0};"
          "size_t len = sizeof \2 / sizeof \2[0];"
          "size_t start= \3+0>=0?\3+0:\3 +len;"
          "size_t end = \4+0?\4:len\4;"
          "for(size_t i=start;i<end;i++) tmp[i-start]=\2[i]; tmp;})\5");
        // Implements `myCmd myLabel in array[[start][:end]]`
        #define INARRAY \
          "\\s*(\\w+)\\s+in\\s+([^:\" ]+)\\s*(\\[\\s*(-[^]:]+)?([^]:]+)?"   \
          "\\s*:\\s*(-[^]:]+)?([^]:]+)?\\s*\\])?"                           //
        #define LOOP \
          "for(size_t \1_index=0\4?sizeof \2/sizeof \2[0]\4:\5+0,"          \
          "\1_end=\7+0?\7+0:sizeof \2/sizeof \2[0]\6;(\1=\2[\1_index])"     //
        #define INCREMENT "\1_index<\1_end;\1_index++)"
        // for myLabel in array[[start][:end]]
        SUB("for" INARRAY, LOOP "," INCREMENT);
        // foreach
        SUB("foreach" INARRAY, "void *\1; for(size_t \1_index=0;(\1=\2[\1_index]);\1_index++)");
        // while myLabel in array[[start][:end]]
        SUB("while" INARRAY, LOOP "&&" INCREMENT);
        #define ARGSP "(( ?[^ \"]| ?\"(\\\\.|[^\\\"])*\")*) ?(\\s+|$)"
        // until
        SUB("(\\s|^)until\\s*" ARGSP, "\1while (!(\2))\5");
        // unless
        SUB("(\\s|^)unless\\s*" ARGSP, "\1if (!(\2))\5");
         // double-space = parenthesis
        SUB("(\\w)  " ARGSP, "\1(\2)\5");
        // Put function-like macros here
        // println()
        // tmp will contain argument list; match holds var assignment, if any
        // need to do it twice because we only have greedy regex
        if((tmp = resub(*s, ".*(sp|fp|ep)rin(t|tln)\\s*\\((.*)\\).*", "\1, \3, \2_")) || (tmp = resub(*s, ".*prin(t|tln)\\s*\\((.*)\\).*", "p, \2, \1_"))){
            !(match = resub(*s, "(.*)(sp|fp|ep)rint.*\\(.*", "\1") )?
              match = resub(*s, "(.*)print.*\\(.*", "\1") : match;
            strcpy(*s, match);
            // token split argument string by commas and spaces
            char *ep, *pre = "", *pc = "", *cmd, *args[MAX_TOKENS] = {NULL};
            int b = 0, token_count = split_print_args(tmp, args);
            ep = args[b++];
            if(ep[0] == 's' || ep[0] == 'f') {// sprint/fprint
                pre = args[b++]; pc = ", ";}
            for(int i=b; i < token_count - 1; i++){
                // if not println end print with a space "_()"
                if(strcmp(args[i + 1], "tln_")){
                    strcat(*s, aargcat(cmd, ep, "_(", pre, pc, args[i], ")"));}
                else {// otherwise print a new line "n_()"
                    strcat(*s, aargcat(cmd, ep, "n_(", pre, pc, args[i], ")"));}}
            // Free dynamically allocated memory
            for(int i = 0; i < token_count; i++){
                free(args[i]);}
            free(tmp);
            free(match);}
        // repeat
        SUB("repeat\\s*\\(([^, ]+)[, ]*(\\w*)\\)",
         "for(size_t \2_index=\1;\2_index--;)");
        // skip over multi-line comments
        if((tmp = resub(*s,"(/[*])(.*[^/]$)", "\1\2"))){
            strcpy(skip.to, "([*]/)") ;strcpy(skip.end, "\1");
            free(tmp) ; INDENT; return;}
        // triple quotes
        if((tmp = resub(*s,"\"{3}(.*)\"{3}", "\"\1"))){
            addcslashes(tmp+1);
            strcpy(*s, tmp) ;strcat(*s, "\"") ;free(tmp);}
        // multi-line triple quotes
        else if((tmp = resub(*s,"(.*)\"{3}(([^\"]+\"?)*)", "\"\2"))){
            addcslashes(tmp+1);
            match = resub(*s,"\"{3}(([^\"]+\"?)*)", tmp);
            strcpy(skip.to, "(.*)\"{3}") ;strcpy(skip.end, "\1");
            strcpy(*s, match) ;free(tmp) ;free(match) ;INDENT;}
        // apply embedded macros
        for(struct macro *m = maclist;m ;m = m->next){
            SUB(m->match, m->replace);}
        // read embedded macros
        match = resub(*s, "#replace\\s+/(.*)/(.*)/", "\1");
        changed= resub(*s, "#replace\\s+/(.*)/(.*)/","\2");
        if(match && changed){
            macro_append(&maclist, match, changed);}
        else{
            free(match) ;free(changed);}
        SUB("#replace\\s+/(.*)/(.*)/", "\x2f/ crap: replaced \1 with \2");}
    return;
}
#undef ARGSP
#undef INARRAY
#undef LOOP
#undef INCREMENT
#undef SUB
void cut_eol(char **fc, char **lc){
    // slice off end of line comments, store in $eol
    // needed to insert semicolon before comments
    char *broil = resub(*fc,"([ \t]*/\\*[^/]*\\*/)?[\\ \n]*$|[/]{2}.*$", "");
    *lc = *fc + strlen(broil) ;free(broil);
    strcpy(eol, *lc) ;**lc = '\0'; (*lc)--;}
char *prepend(char *dest, char *src){
    // Requires writable memory *before* dest.
    // Caller may choose to keep original pointer or
    // reassign it with s = prepend(s, "some text")
    size_t srclen = strlen(src); dest -= srclen;
    memcpy(dest, src, srclen) ; return dest;}
void decorate(char **s){
    static char plc = ' ';
    char *tmp;
    // convert tabs to spaces
    replace(*s, "\t", SPACES);
    // locate first non-whitespace chr
    int spaces = strspn(*s, " ");
    char *fc = *s + spaces, *lc = strrchr(*s, '\n');
    if(!(*skip.to) && fc < lc) indent = ((fc - *s) | 0x03) ^ 0x03;
    *s = prepend(*s, eol);
    while(indent < prev_indent){
        *s = prepend(*s, "}") ;prev_indent -= TAB;}
    cut_eol(&fc, &lc);
    // if we have skipped to the end of a long comment or quote
    if(*(skip.to) && (tmp = resub(*s, skip.to, "\1"))){
        strcpy(*s, tmp) ; free(tmp);
        // and if not a comment, end the last line with a quote
        if(strcmp(skip.to, "([*]/)")) *s = prepend(*s, "\\n\"");
        // stop the skip.to algorithm
        *(skip.to) = '\0', *skip.end = 2;}
    if (!(plc == '\\' || *fc == 34 || *(skip.end) || indent != prev_indent)){
        *s = prepend(*s, ";");}
    if(!strcmp(skip.to, "(.*)\"{3}")){
        addcslashes(*s);}
    if(!*skip.to) macros(&fc);
    if(*(skip.to) || (*(skip.end) && --(*(skip.end)))) return;
    lc = *s + strlen(*s) - 1; if(lc < *s) return;
    // skip semicolon on lines ending with punc.
    if(strchr(" <>:;,.=*/&|^!?", *lc)){
        *(skip.end) = 1;}
    // skip semicolon on blank lines
    if(strlen(fc) == 0) *(skip.end) = 1;
    // skip semicolon on defines
    if(*fc=='#') *(skip.end) = 1;
    plc = *lc;
    INDENT;}
int crap(char *name){
    char buf[MAX_LINE_LEN + BACK_BUFFER_LEN], *b;
    FILE *f = stdin;
    if (strcmp(name, "-")) f = fopen(name, "r");
    if (!(f)){
        fprintf(stderr, "crap: Unable to open \"%s\" for reading.\n", name);
        return 1;}
    while (!(feof(f) || ferror(f))){
        b = buf + BACK_BUFFER_LEN;
        if(fgets(b, MAX_LINE_LEN, f)){
            if(b[strlen(b)-1]!='\n') strcat(b, "\n");
            decorate(&b) ;printf("%s", b);}}
    fclose(f);
    if (!(strchr("#}()<", b[0]))) {// final #endif, brace, tag?
        if(has_main) strcpy(b, SPACES "return 0;\n}\n");
        else strcpy(b, "}");
        decorate(&b) ;puts(b);}
    else puts("");
    macro_free(&maclist);
    return 0;}
int main(int argc, char **argv, char **env){
    if(argc < 2) puts("usage: crap infile [> outfile]");
    else return crap(argv[1]);
    return 0;
}
