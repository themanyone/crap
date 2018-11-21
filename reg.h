#ifndef __REG_H__
#define __REG_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

// Our implementation limit is 31 octal backrefs
// because chr(32) is a space, and we need that!
#define NMATCH 31

// Concatenate part of s onto buf.
// We only want part of s, not the whole string.
#define STRNCAT(buf, s, len) 		\
({ size_t sb = strlen(buf);			\
buf = realloc(buf, sb + len + 1); 	\
*(buf + sb + len) = '\0'; 			\
memcpy(buf + sb, s, len); })

struct macro{
    char *match, *replace;
    struct macro *next;
};

char *unescape_octal(char *);
void macro_append(struct macro **, char *, char *);
void macro_prepend(struct macro **, char *, char *);
void macro_free(struct macro **);
char *resub(const char *, const char *, const char *);

#endif //__REG_H__
