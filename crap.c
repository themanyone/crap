//bin/crap "$0" |tcc -Llibs -lreg -run - "$@";exit 0
/** Concise, Regex-Aware Preprocessor (CRAP);
 * a C (computer language) code decorator and language maker;
 */
/* Copyright (C) 2018-2019 Henry Kroll III, https://thenerdshow.com

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
#include "join.h"
struct{
    char to[7], end[3];}
skip = {{'\0'}, {'\2'}};
char *has_main=NULL, eol[255]={'\0'};
struct macro *maclist = NULL;
void macros(char **s){
    char *tmp, *match, *replace;
    // check if we are done skipping over a multiline comment, triple-quote
    if(skip.to[0] && (tmp = resub(*s, skip.to, skip.end))){
        free(tmp);
        skip.to[0] = '\0', skip.end[0] = 2;}
    else{
        // put keyword macros here
        // TODO: exclude content inside strings
        // main becomes int main()
        if(!(has_main || strcmp(*s, "main"))){
            has_main = strcpy(*s, "int main(int argc, char **argv, char** env)");}
        int max;
        #define SUB(match, rep)                     \
        max = MAX_REPLACE;                           \
        while(max-- && (tmp=resub(*s, match, rep))){ \
            strcpy(*s, tmp) ;free(tmp);}
        // array[:] notation now works most places (do not free)
        //   \1        \2         [ \3      :    \4     ]   \5
        SUB("([(*,=]\\s*|  )([^[\" ]+)\\s*\\[(\\w*):(\\w*)\\]([[);, ]+|$)",
          "\1({void *t;typeof(\2) tmp = {0};"
          "size_t len = sizeof \2 / sizeof \2[0];"
          "size_t start= \3+0>=0?\3+0:\3 +len;"
          "size_t end = \4+0?\4:len\4;"
          "for(size_t i=start;i<end;i++) tmp[i-start]=\2[i]; tmp;})\5");
        // for pointer in array[[start][:end]] (may be negative)
        SUB("for\\s*(\\w+)\\s+in\\s+([^[\" ]+)\\s*(\\[\\s*(-[^]:]+)?([^]:]+)?"
          "\\s*:?\\s*(-[^]:]+)?([^]:]+)?\\s*\\])?",
          "for(size_t \1_index=0\4?sizeof \2/sizeof \2[0]\4:\5+0,"
          "\1_end=\7+0?\7:sizeof \2/sizeof \2[0]\6;"
          "\1_index<\1_end&&(\1=\2[\1_index]);\1_index++)");
        // while pointer in array[[start][:end]] (may be negative)
        SUB("while\\s*(\\w+)\\s+in\\s+([^[\" ]+)\\s*(\\[\\s*(-[^]:]+)?([^]:]+)?"
          "\\s*:?\\s*(-[^]:]+)?([^]:]+)?\\s*\\])?",
          "for(size_t \1_index=0\4?sizeof \2/sizeof \2[0]\4:\5+0,"
          "\1_end=\7+0?\7:sizeof \2/sizeof \2[0]\6;"
          "\1_index<\1_end&&\2[\1_index]&&(\1=\2[\1_index]);\1_index++)");
        // double-space = parenthesis
        SUB("(\\w)  (( ?[^ \"]+| ?\".*\")*) ?([ ;]|$)", "\1(\2)\4");

        // Put function-like macros here
        // repeat
        SUB("repeat\\s*\\(([^, ]+)[, ]*([^, ]*)\\)",
         "for(size_t \2_index=\1;\2_index--;)");
        // until
        SUB("until\\s*\\((.+)\\)", "while(!(\1))");
        // unless
        SUB("unless\\s*\\((.+)\\)", "if(!(\1))");
        // skip over multi-line comments
        if((tmp = resub(*s,"(/\\*)(.*[^/)]$)", "\1\2"))){
            strcpy(skip.to, "(\\*/)");
            strcpy(skip.end, "\1");
            free(tmp) ;return;}
        // FIXME: triple quotes
        if((tmp = resub(*s,"\"\"\"(([^\"]+\"?)*)", "\"\2"))){
            strcpy(skip.to, "(.*)\"\"\"");
            strcpy(skip.end, "\1\"");
            strcpy(*s, tmp) ;free(tmp) ;return;}
        // apply embedded macros
        for(struct macro *m = maclist;m ;m = m->next){
            SUB(m->match, m->replace);}
        // read embedded macros
        match = resub(*s, "#replace\\s+/(.*)/(.*)/", "\1");
        replace= resub(*s, "#replace\\s+/(.*)/(.*)/","\2");
        if(match && replace){
            macro_append(&maclist, match, replace);}
        else{
            free(match) ;free(replace);}
        SUB("#replace\\s+/(.*)/(.*)/", "\x2f/ crap: replaced \1 with \2");}
    return;}
#undef SUB
void cut_eol(char **fc, char **lc){
    // slice off end of line comments, store in $eol
    // needed to insert semicolon before comments
    char *broil = resub(*fc,"([ \t]*/\\*[^/]*\\*/)?[\\ \n\t]*$|[/]{2}.*$", "");
    *lc = *fc + strlen(broil) ;free(broil);
    strcpy(eol, *lc) ;**lc = '\0'; (*lc)--;}
char *prepend(char *dest, char *src){
    // Requires writable memory *before* dest.
    // Caller may choose to keep original pointer or
    // reassign it with s = prepend(s, "some text")
    size_t srclen = strlen(src); dest -= srclen;
    memcpy(dest, src, srclen) ; return dest;}
void decorate(char **s){
    static int prev_indent = 0, indent = 0;
    char *t;
    // convert tabs to spaces
    while((t = resub(*s, "\t", "    "))){
        strcpy(*s, t) ;free(t);}
    // locate first non-whitespace char
    int spaces = strspn(*s, " ");
    char *fc = *s + spaces, *lc = strrchr(*s, '\n');
    if(!(*skip.to) && fc < lc) indent = ((fc - *s) | 0x03) ^ 0x03;
    *s = prepend(*s, eol);
    while(indent < prev_indent){
        *s = prepend(*s, "}");
        prev_indent -= TAB;}
    cut_eol(&fc, &lc);
    if(!(*(skip.end) || indent != prev_indent)){
        *s = prepend(*s, ";");}
    macros(&fc);
    if(*(skip.to) || (*(skip.end) && --(*(skip.end)))) return;
    lc = *s + strlen(*s) - 1; if(lc < *s) return;
    // skip semicolon on lines ending with punc.
    if(strchr(" <>;,.\"=*/&|^!", *lc)) *(skip.end) = 1;
    // skip semicolon on blank lines
    if(strlen(fc) < 1) *(skip.end) = 1;
    // skip semicolon on defines
    if(*fc=='#') *(skip.end) = 1;
    // add braces
    while(indent > prev_indent){
        *s = prepend(*s, "{") , prev_indent += TAB;}}
int crap(char *name){
    char buf[MAX_LINE_LEN + BACK_BUFFER_LEN], *b;
    FILE *f = stdin;
    if (strcmp(name, "-")) f = fopen(name, "r");
    if(!(f)){
        fprintf(stderr, "crap: Unable to open \"%s\" for reading.\n", name);
        return 1;}
    while(!(feof(f) || ferror(f))){
        b = buf + BACK_BUFFER_LEN;
        if(fgets(b, MAX_LINE_LEN, f)){
            decorate(&b) ;printf("%s", b);}}
    fclose(f);
    if(!(strstr(b, "#endif"))){
        if(has_main) strcpy(b, "    return 0;\n}\n");
        else strcpy(b, "    \n}\n");
        decorate(&b) ;puts(b);}
    macro_free(&maclist);
    return 0;}
int main(int argc, char **argv, char** env){
    if(argc < 2) puts("usage: crap infile [> outfile]");
    else return crap(argv[1]);
    return 0;
}
