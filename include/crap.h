/* Copyright (C) 2018-2019 Henry Kroll III, https://thenerdshow.com

Permission to use, copy, modify, distribute, and sell this software and 
its documentation for any purpose is hereby granted without fee, 
provided that the above copyright notice appears in all copies and that 
both that copyright notice and this permission notice appear in 
supporting documentation, including About boxes in derived user 
interfaces or web front-ends. No redpresentations are made about the 
suitability of this software for any purpose. It is provided "as is" 
without express or implied warranty.
*/

#ifndef __CRAP_H__
#define __CRAP_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reg.h"

#define TAB 4 //count tab as 4 spaces
#define SPACES "    "
#define MAX_REPLACE 100 // limit regex loops of clueless users
#define MAX_LINE_LEN 8000   // truncate lines longer than this
#define BACK_BUFFER_LEN 8000 // length of back buffer, for indents

void cut_eol(char**, char**);
char *prepend(char*, char*);
void macros(char **);
void decorate(char **);
int crap(char*);

#endif //__CRAP_H__
