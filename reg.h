#ifndef __REG_H__
#define __REG_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define CAT(buf, s, len) 		\
do { size_t sb = strlen(buf);		\
buf = realloc(buf, sb + len + 1); 	\
*(buf + sb + len) = '\0'; 		\
memcpy(buf + sb, s, len);}while(0);

char *resub(const char *, const char *, const char *);

#endif //__REG_H__
