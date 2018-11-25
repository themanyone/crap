#ifndef __JOIN_H__
#define __JOIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#include <string.h>

//join an array into a string
#define JOIN(arr) ({                             \
    char *b="", **j = arr;                        \
    while(*j && (b = ARGCAT(b, *j++)));           \
    b;}                                            \
) //

/** join strings with NULL arg or pathsep
  * works like Python's "/".join["c:", "dog", "cat"]

  * XXX inherits quirks of alloca(): see `man alloca` XXX
  */
#define ARGJOIN(sep, ...) ({                             \
    char *s[]={__VA_ARGS__};                              \
    char* _return = alloca(sizeof s); _return[0]='\0';    \
    size_t len = sizeof s/sizeof s[0];                    \
    for(size_t ix = 0; ix < len; ix++){                   \
        strcat(strrchr(_return,'\0'), s[ix]);             \
        if(ix<len-1) strcat(strrchr(_return,'\0'), sep);} \
    _return;}                                              \
) //

/** like AJOIN with no separator */
#define ARGCAT(...) ARGJOIN("", __VA_ARGS__)
/** split strings with arg or path sep
  * returns ARRAY_MAX elements in dynamic array
  */
#define ARRAY_MAX 100
#define SPLIT(s, sep)  ({                               \
    size_t len = strlen(sep);                            \
    char *a[ARRAY_MAX] = {NULL};                         \
    int i=0; for (a[i++] = strtok(s, sep);               \
    (a[i++] = strtok(NULL, sep) );                      \
    );a[len]=NULL;a;}                                    \
) //

#endif 