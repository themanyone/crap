;//bin/crap "$0" |tcc -Llibs -lreg -run - "$@";exit 0
/** Concise, Regex-Aware Preprocessor (CRAP)
 * a C (computer language) code decorator and language maker
 */
/* Copyright (C) 2018-2019 Henry Kroll III, https://thenerdshow.com

Permission to use, copy, modify, distribute, and sell this software and 
its documentation for any purpose is hereby granted without fee, 
provided that the above copyright notice appears in all copies and that 
both that copyright notice and this permission notice appear in 
supporting documentation, including About boxes in derived user 
interfaces or web front-ends. No representations are made about the 
suitability of this software for any purpose. It is provided "as is" 
without express or implied warranty.
*/
#include "crap.h"
static struct{
    char to[255], end[255];}
skip = {{'\0'}, {'\1'}};
static char *has_main=NULL, eol[255]={'\0'};
static void macros(char **s){
    char *tmp = NULL;
    // check if we are done skipping over a multiline comment
    if(skip.to[0] && (tmp = resub(*s, skip.to, skip.end))){
        free(tmp);
        skip.to[0] = '\0', skip.end[0] = 2;}
    else{
        // put non-function macros here
        // main becomes int main()
        if(!has_main && !strcmp(*s, "main")){
            has_main = strcpy(*s, "int main(int argc, char **argv)");}
        #define SUB(match, rep)              \
        while((tmp=resub(*s, match, rep))){     \
            strcpy(*s, tmp) ;free(tmp);}
        // for..x..in..y
        SUB("for\\s*(\\w+)\\s+in\\s+(\\w+)", 
          "for(size_t \1_index=0,\1_len=len(\2);" 
          "\1_index<\1_len&&(\1=\2[\1_index]);" 
          "\1_index++)");
        // read embedded macros
        // TODO: apply them
        SUB("#replace\\s+\"(.*)\"\\s+with\\s+\"(.*)\"", 
        "// \"\1\" becomes \"\2\"")
        // double-space = parenthesis
        SUB("(\\w)  (( ?[^ \"]+| ?\".*\")*) ?([ ;]|$)", "\1(\2)\4");

        // Put function-like macros here
        // repeat
        SUB("repeat\\s*\\(([^)]+)\\)", "for(size_t _=\1;_--;)");
        // until
        SUB("until\\s*\\(([^)]+)\\)", "while(!\1)");
        // unless
        SUB("unless\\s*\\(([^)]+)\\)", "if(!\1)");
        #undef SUB
        // skip over multi-line comments
        if((tmp = resub(*s,"(/\\*)(.*[^/]$)", "\1\2"))){
            free(tmp);
            strcpy(skip.to, "(\\*/)");
            strcpy(skip.end, "\1");}}}
static void cut_eol(char **fc, char **lc){
    // slice off end of line comments, store in $eol
    // needed to insert semicolon before comments
    char *broil = resub(*fc,"([ \t]*/\\*[^/]*\\*/)?[\\ \n\t]*$|[/]{2}.*$", "");
    *lc = *fc + strlen(broil) ;free(broil);
    strcpy(eol, *lc) ;**lc = '\0'; (*lc)--;}
static char *prepend(char *dest, char *src){
    // Requires writable memory *before* dest.
    // Returns pointer to *new* beginning.
    // Caller may choose to keep original pointer or
    // reassign it with s = prepend(s, "some text")
    size_t srclen = strlen(src);
    dest -= srclen;
    memcpy(dest, src, srclen);
    return dest;}
static void decorate(char **s){
    static int prev_indent = 0, indent = 0;
    // convert tabs to spaces
    char *t;
    while((t = resub(*s, "\t", "    "))){
        strcpy(*s, t) ;free(t);}
    // locate first non-whitespace char
    int spaces = strspn(*s, " ");
    char *fc = *s + spaces, *lc = strrchr(*s, '\n');
    if(!(*skip.to) && fc < lc) indent = ((fc - *s) | 0x03) ^ 0x03;
    if(indent < prev_indent){
        *s = prepend(*s, eol);
        while(indent < prev_indent){
            *s = prepend(*s, "}");
            prev_indent -= TAB;}}
    else *s = prepend(*s, eol);
    char *ll = eol + strlen(eol) - 2;
    if(*ll == ' ') *(skip.end) = 1;
    if(!*(skip.end) && indent == prev_indent){
        *s = prepend(*s, ";");}
    cut_eol(&fc, &lc);
    macros(&fc);
    if(*(skip.to) || (*(skip.end) && --(*(skip.end)))) return;
    lc = *s + strlen(*s) - 1; if(lc < *s) return;
    // skip semicolon on lines ending with punc.
    if(strchr("<>;,.=*/&|^!", *lc)) *(skip.end) = 1;
    // skip semicolon on blank lines
    if(strlen(fc) < 3) *(skip.end) = 1;
    // skip semicolon on defines
    if(*fc=='#') *(skip.end) = 1;
    // add braces
    while(indent > prev_indent){
        *s = prepend(*s, "{");
        prev_indent += TAB;}}
static int crap(char *name){
    char buf[MAX_LINE_LEN + BACK_BUFFER_LEN], *b;
    FILE *f = fopen(name, "r");
    if(!f){
        fprintf(stderr, "crap: Unable to open \"%s\" for reading.\n", name);
        return 1;}
    while(!feof(f) && !ferror(f)){
        b = buf + BACK_BUFFER_LEN;
        if(fgets(b, MAX_LINE_LEN, f)){
            decorate(&b);
            printf("%s", b);}}
    fclose(f);
    if(has_main) strcpy(b, "    return 0;\n}\n");
    else strcpy(b, "    \n}\n");
    decorate(&b);
    puts(b);
    return 0;}
int main(int argc, char **argv){
    if(argc < 2) puts("usage: crap infile [> outfile]");
    else return crap(argv[1]);
    return 0;
    
}
