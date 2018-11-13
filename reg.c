#include <stdio.h>
#include "reg.h"
char *resub (const char *text, const char *pattern, const char *replacement){
    // text replacement with up to \7 octal backref substitutions
    int status;
    char *output = calloc(100,1);
    regmatch_t pm[8];
    regex_t re;
    if (!(status = regcomp(&re, pattern, REG_EXTENDED)) 
    && !(status = regexec(&re, text, 8, pm, 0))){
        int i, len;
        CAT (output, text, pm[0].rm_so);
        while (1){
            len = strcspn(replacement, "\1\2\3\4\5\6\7");
            // append output up-to backref
            CAT (output, replacement, len);
            if (!(i = replacement[len]))break;
            replacement += len + 1;
            // append pattern match pm[i]
            len = pm[i].rm_eo - pm[i].rm_so;
            CAT (output, text+pm[i].rm_so, len);}
        text += pm[0].rm_eo; len = strlen (text);
        CAT (output, text, len);}
    else if (regerror(status, &re, output, 99)){
        free (output);
        return NULL;}
    regfree (&re);
    return output;
    return 0;
}
