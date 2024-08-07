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

#define printf_dec_format(x, y) _Generic((x), \
char: "%d" y, \
signed char: "%hhd" y, \
unsigned char: "%hhu" y, \
signed short: "%hd" y, \
unsigned short: "%hu" y, \
signed int: "%d" y, \
unsigned int: "%u" y, \
long int: "%ld" y, \
unsigned long int: "%lu" y, \
long long int: "%lld" y, \
unsigned long long int: "%llu" y, \
float: "%f" y, \
double: "%f" y, \
long double: "%Lf" y, \
char *: "%s" y, \
void *: "%s" y) //

size_t cp_ = 0;

size_t total_printed()
    size_t c = cp_
    cp_ = 0
    return c

#define px_(x)  cp_+=printf(printf_dec_format(x,), x)
#define p_(x)   cp_+=printf(printf_dec_format(x, " "), x)
#define pn_(x)  cp_+=printf(printf_dec_format(x, "\n"), x)

#define epx_(x) cp_+=fprintf(stderr, printf_dec_format(x,), x)
#define ep_(x)  cp_+=fprintf(stderr, printf_dec_format(x, " "), x)
#define epn_(x) cp_+=fprintf(stderr, printf_dec_format(x, "\n"), x)

#define spx_(s, x) cp_+=sprintf(strrchr((s), 0), printf_dec_format(x,), x)
#define sp_(s, x)  cp_+=sprintf(strrchr((s), 0), printf_dec_format(x, " "), x)
#define spn_(s, x) cp_+=sprintf(strrchr((s), 0), printf_dec_format(x, "\n"), x)

#define fpx_(f, x) cp_+=fprintf(f, printf_dec_format(x,), x)
#define fp_(f, x)  cp_+=fprintf(f, printf_dec_format(x, " "), x)
#define fpn_(f, x) cp_+=fprintf(f, printf_dec_format(x, "\n"), x)

#define debugf(...) DEBUG && fprintf(stderr, FL __VA_ARGS__)

#if 0
// We can then print values like so:
    p_('a');    // prints "97" (on an ASCII system)
    p_((char)'a');  // prints "a"
    p_(123);    // prints "123"
    p_(1.234);      // prints "1.234000"
#endif

#define MAX_TOKENS 1000
#define MAX_TOKEN_LEN 5000

#define STR_(x) #x
#define STRINGS_(x) STR_(x)
#define FL __FILE__""STRINGS_(:__LINE__)" "

typedef enum
    NORMAL,
    QUOTED = '"',
    SQUOTED= '\'',
    PARENS = ')',
State;

char *strdup  const char *s
    size_t len = strlen(s) + 1
    char *dup = malloc(len)
    if  dup != NULL
        memcpy  dup, s, len
    return dup

int split_print_args  char *str, char **tokens
    State state = NORMAL
    int token_count = 0
    char token[MAX_TOKEN_LEN] = {0}
    int token_index = 0

    for  int c, i = 0; (c=str[i]); i++
        char *end = ""
        int tl = strlen(token)
        if  tl  end = token + tl - 1
        switch  state
            case NORMAL:
            switch  c
                case '\'':
                state = SQUOTED
                token[token_index++] = '"'
                break
                case '"':
                state = QUOTED
                token[token_index++] = '"'
                break
                case '(':
                state = PARENS
                token[token_index++] = c
                break
                case ',': case ' ':
                if  token_index > 0
                    tokens[token_count++] = strdup(token)
                    token_index = 0
                    memset  token, 0, MAX_TOKEN_LEN
                break
                default:
                    token[token_index++] = c
            break
            default:
            if  *end != '\\'
                if  c == state
                    state = NORMAL
                    if  c == '\''  c = '"'
            token[token_index++] = c
        if  token_count > MAX_TOKENS
            fprintf  stderr, FL "Token length exceeded\n"
            break
    if  token_index > 0
        tokens[token_count++] = strdup  token
    tokens[token_count] = NULL
    return token_count

#endif //__print_h
