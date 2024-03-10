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
/* From http://www.robertgamble.net/2012/01/c11-generic-selections.html

This allows the creation of a macro that can print any type of value that printf
supports without having to specify the type explicitly in the call: */

#ifndef __print_h
#define __print_h
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define printf_dec_format(x) _Generic((x), \
char: "%d", \
signed char: "%hhd", \
unsigned char: "%hhu", \
signed short: "%hd", \
unsigned short: "%hu", \
signed int: "%d", \
unsigned int: "%u", \
long int: "%ld", \
unsigned long int: "%lu", \
long long int: "%lld", \
unsigned long long int: "%llu", \
float: "%f", \
double: "%f", \
long double: "%Lf", \
char *: "%s", \
void *: "%s") //

#define print1(x) printf(printf_dec_format(x), x)
#define print1n(x) printf(printf_dec_format(x), x), putchar('\n')

#if 0
{// We can then print values like so:
    print1(('a'));    // prints "97" (on an ASCII system)
    print1('a');  // prints "a"
    print1(123);    // prints "123"
    print1(1.234);      }// prints "1.234000"
#endif

#define MAX_TOKENS 100
#define MAX_TOKEN_LEN 256

typedef enum{
    NORMAL,
    QUOTED,
    PARENS,}
State;

char *strdup(const char *s){
    size_t len = strlen(s) + 1;
    char *dup = malloc(len);
    if(dup != NULL){
        memcpy(dup, s, len);}
    return dup;
}
int split_print_args(char *str, char **tokens){
    State state = NORMAL;
    int token_count = 0;
    char token[MAX_TOKEN_LEN] = {0};
    int token_index = 0;

    for(int c, i = 0; (c=str[i]); i++){
        switch(state){
            case NORMAL:
            switch(c){
                case '\'': case '"':
                state = QUOTED;
                token[token_index++] = '"';
                break;
                case '(':
                state = PARENS;
                token[token_index++] = c;
                break;
                case ',': case ' ':
                if(token_index > 0){
                    tokens[token_count] = strdup(token);
                    token_count++;
                    token_index = 0;
                    memset(token, 0, MAX_TOKEN_LEN);}
                break;
                default:{
                    token[token_index++] = c;}}
            break;
            case QUOTED:
            if((c == '\'' || c == '\x22')){
                state = NORMAL;
                c = '"';}
            token[token_index++] = c;
            break;
            case PARENS:
            if(c == ')'){
                state = NORMAL;}
            token[token_index++] = c;
            break;
}}
    if(token_index > 0){
        tokens[token_count] = strdup(token);
        token_count++;
}
    tokens[token_count] = NULL;
    return token_count;
}
#endif 
