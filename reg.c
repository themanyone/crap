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
char *unescape_backref(char * const s){
    char *s1 = s, *e = strrchr(s1, '\0');
    while((s1+=strcspn(s1, "\\")) < e){
        unsigned long int backref = strtoul(++s1, NULL, 10);
        if(!(backref && backref < 32)) continue;
        *(s1-1)=backref;
        int s2 = strspn(s1, "0123456789");
        memmove(s1, s1+s2, strlen(s1+s2)+1);}
    return s;}
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
        head->replace = unescape_backref(replace);
        head->next = NULL;}
    return;}
void macro_prepend(struct macro **sm, char *match, char *replace){
    struct macro *next = *sm;
    if((*sm = malloc(sizeof (struct macro)))){
        (*sm)->replace = unescape_backref(replace);
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
    // text replacement with up to \31 decimal backrefs
    int status;
    char *output = calloc(100,1);
    regmatch_t pm[NMATCH];
    regex_t re;
    if (!(status = regcomp(&re, pattern, REG_EXTENDED)) &&
      !(status = regexec(&re, text, NMATCH, pm, 0))){
        int i, len;
        STRNCAT(output, text, pm[0].rm_so);
        char dec[32]={'\0'};
        for(int x=32;--x;) dec[x-1]=x;
        while(1){
            len = strcspn(replacement, dec);
            // append output up-to backref
            STRNCAT(output, replacement, len);
            if(!(i = replacement[len])) break;
            replacement += len + 1;
            // append pattern match pm[i]
            len = pm[i].rm_eo - pm[i].rm_so;
            STRNCAT(output, text+pm[i].rm_so, len);}
        text += pm[0].rm_eo; len = strlen(text);
        STRNCAT(output, text, len);}
    else if(regerror(status, &re, output, 99)){
        free(output) ;output = NULL;}
    regfree(&re);
    return output;
    
}
