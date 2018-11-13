#include <stdio.h>
#include "crap.h"
static struct skip{
    char to[255];
    char end[255];}
skip = {{'\0'}, {'\1'}};
static char eol[255]={'\0'};
static void macros (char **s){
    char *tmp = NULL;
    // end of multiline match
    if (skip.to[0] && (tmp = resub(*s, skip.to, skip.end))){
        free (tmp);
        skip.to[0] = '\0';
        skip.end[0] = 2;}
    else{
        // handle extended macros here

        // main
        if (!strcmp(*s, "main")){
            strcpy(*s, "int main(int argc, char **argv)");}
        // double-space = parenthesis
        while ((tmp = resub(*s,"([0-9A-z_])  (([ ]?[^ \"]+|[ ]?\".*\")*)(  |$)", "\1 (\2)"))){
            strcpy (*s, tmp);free (tmp);}
        // repeat
        if ((tmp = resub(*s,"repeat[ \t]*\\(([^),]*)?\\)",
        "for(int i=\1;i--;)"))){
            strcpy (*s, tmp);free (tmp);}
        // multi-line comments
        if ((tmp = resub(*s,"(/\\*)(.*[^/]$)", "\1\2"))){
            free (tmp);
            strcpy (skip.to, "(\\*/)");
            strcpy (skip.end, "\1");}}}
static void cut_eol (char **fc, char **lc){
    // slice off end of line comments, store in $eol
    // needed to insert semicolon before comments
    char *broil = resub(*fc,"([ \t]*/\\*[^/]*\\*/)?[\\ \n\t]*$|[/]{2}.*$", "");
    *lc = *fc + strlen (broil);free (broil);
    strcpy (eol, *lc);**lc = '\0'; (*lc)--;}
static char *prepend (char *dest, char *src){
    // Requires writable memory *before* dest.
    // Returns pointer to *new* beginning.
    // Caller may choose to keep original pointer or
    // reassign it with s = prepend(s, "some text")
    size_t srclen = strlen(src);
    dest -= srclen;
    memcpy (dest, src, srclen);
    return dest;}
static void decorate (char **s){
    static int prev_indent = 0, indent = 0;
    // convert tabs to spaces
    char *t;
    while ((t = resub(*s, "\t", "    "))){
        strcpy (*s, t);free (t);}
    // locate first non-whitespace char
    int spaces = strspn(*s, " ");
    char *fc = *s + spaces, *lc = strrchr(*s, '\n');
    if (!(*skip.to) && fc < lc)indent = ((fc - *s) | 0x03) ^ 0x03;
    if (indent < prev_indent){
        *s = prepend (*s, eol);
        while (indent < prev_indent){
            *s = prepend (*s, "}");
            prev_indent -= TAB;}}
    else *s = prepend (*s, eol);
    char *ll = eol + strlen(eol) - 2;
    if (*ll == ' ')*(skip.end) = 1;
    if (!*(skip.end) && indent == prev_indent){
        *s = prepend (*s, ";");}
    cut_eol (&fc, &lc);
    macros (&fc);
    if (*(skip.to) || (*(skip.end) && --(*(skip.end))))return;
    lc = *s + strlen(*s) - 1; if (lc < *s)return;
    // skip semicolon on lines ending with punc.
    if (strchr("<>;,=*/&|^!", *lc))*(skip.end) = 1;
    // skip semicolon on defines or multi
    if (*fc=='#' || *lc == '\\')*(skip.end) = 1;
    // skip semicolon on blank lines
    if (strlen(fc) < 3)*(skip.end) = 1;
    // add braces
    while (indent > prev_indent){
        *s = prepend (*s, "{");
        prev_indent += TAB;}}
static int crap (char *name){
    char buf[1100], *b;
    int intro = 1;
    FILE *f = fopen (name, "r");
    if (f)do{
        b = buf + 100;
        if (fgets(b, 1000, f)){
            if (intro){
                intro = 0;
                strcpy (b, "#include <stdio.h>\n");}
            decorate (&b);
            printf ("%s", b);}}
    while (!feof(f) && !ferror(f));
    else return 1;
    fclose (f);
    strcpy (b, "    \n");
    decorate (&b);
    printf ("%sreturn 0;\n}\n", b);
    return 0;}
int main (int argc, char **argv){
    if (argc < 2)puts ("usage: crap infile [> outfile]");
    else return crap (argv[1]);
    return 0;
    return 0;
}
