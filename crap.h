#ifndef __CRAP_H__
#define __CRAP_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reg.h"

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

#define TAB 4 //count tab as 4 spaces

static void cut_eol(char**, char**);
static char *prepend(char*, char*);
static void macros(char **);
static void decorate(char **);
static int crap(char*);

#endif //__CRAP_H__
