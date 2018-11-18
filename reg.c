//usr/local/bin/anch -keep -run "$0" "$@"; exit 0;
/** resub
 * a terse regex library for code decorating
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
#include "reg.h"
char *unescape_octal(char *replace){
    char pat[3]="\\8"; while(--pat[1] >= '0'){
        char *j; while((j = strstr(replace, pat))){
            *j++ = pat[1]-'0'; while((*j++ = *j));}}
    return replace;}
void macro_append(struct macro **sm, char *match, char *replace){
    struct macro *head = *sm;
    while(head && head->next) head = head->next;
    if(!(head)){
        head = *sm = malloc(sizeof (struct macro));}
    else head = head->next = malloc(sizeof (struct macro));
    if(!(head)){
        fprintf(stderr, "Out of memory.");
        exit(1);}
    else{
        head->match = match;
        head->replace = unescape_octal(replace);
        head->next = NULL;}
    return;}
void macro_prepend(struct macro **sm, char *match, char *replace){
    struct macro *next = *sm;
    if((*sm = malloc(sizeof (struct macro)))){
        (*sm)->replace = unescape_octal(replace);
        (*sm)->match = match, (*sm)->next = next;}
    else fprintf(stderr, "Out of memory.");
    return;}
void macro_free(struct macro **sm){
    while(*sm){
        struct macro *next = (*sm)->next;
        free((*sm)->match) ;free((*sm)->replace);
        free(*sm) ;*sm = next;}
    return;}
char *resub(const char *text, const char *pattern, const char *replacement){
    // text replacement with up to \7 octal backref substitutions
    int status;
    char *output = calloc(100,1);
    regmatch_t pm[8];
    regex_t re;
    if (!(status = regcomp(&re, pattern, REG_EXTENDED)) &&
      !(status = regexec(&re, text, 8, pm, 0))){
        int i, len;
        CAT(output, text, pm[0].rm_so);
        while(1){
            len = strcspn(replacement, "\1\2\3\4\5\6\7");
            // append output up-to backref
            CAT(output, replacement, len);
            if(!(i = replacement[len])) break;
            replacement += len + 1;
            // append pattern match pm[i]
            len = pm[i].rm_eo - pm[i].rm_so;
            CAT(output, text+pm[i].rm_so, len);}
        text += pm[0].rm_eo; len = strlen(text);
        CAT(output, text, len);}
    else if(regerror(status, &re, output, 99)){
        free(output);
        return NULL;}
    regfree(&re);
    return output;
    
}
