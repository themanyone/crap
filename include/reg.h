/* Copyright (C) 2018-2019 Henry Kroll III, https://thenerdshow.com

Permission to use, copy, modify, distribute, and sell this software and 
its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice appears in all copies and that 
both that copyright notice and this permission notice appear in 
supporting documentation, including About boxes in derived user 
interfaces or web front-ends. No redpresentations are made about the 
suitability of this software for any purpose. It is provided "as is" 
without express or implied warranty. */
#ifndef __REG_H__
#define __REG_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

// Our implementation limit is \31 decimal backrefs
// because chr(32) is a space, and we need that!
#define NMATCH 31

// Concatenate part of s onto buf.
// We only want part of s, not the whole string.
// Null-terminate AND realloc makes s bigger
#define STRNCAT(buf, s, len){              \
    size_t sb = strlen(buf);                \
    buf = realloc(buf, sb + len + 100);     \
    *(buf + sb + len) = '\0';             \
    memcpy(buf + sb, s, len);            \
}
struct macro{
    char *match, *replace;
    struct macro *next;}
;
char *unescape_octal(char *);
void macro_append(struct macro **, char *, char *);
void macro_prepend(struct macro **, char *, char *);
void macro_free(struct macro **);
char *resub(const char *, const char *, const char *);

#endif 
