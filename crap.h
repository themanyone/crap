#ifndef __CRAP_H__
#define __CRAP_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reg.h"

#define TAB 4 //count tab as 4 spaces
#define MAX_LINE_LEN 8000   // truncate lines longer than this
#define BACK_BUFFER_LEN 100 // length of back buffer, for indents

static void cut_eol(char**, char**);
static char *prepend(char*, char*);
static void macros(char **);
static void decorate(char **);
static int crap(char*);

#endif //__CRAP_H__
