/*  sjoin.h
    
    string split, join, replace library
    
    Copyright (C) 2018-2019 Henry Kroll III, https://thenerdshow.com
    
    Permission to use, copy, modify, distribute, and sell this 
    software and its documentation for any purpose is hereby 
    granted without fee, provided that the above copyright 
    notice appears in all copies and that both that copyright 
    notice and this permission notice appear in supporting 
    documentation, including About boxes in derived user 
    interfaces or web front-ends. No representations are made 
    about the suitability of this software for any purpose. It 
    is provided "as is" without express or implied warranty.
*/
#ifndef __SPLITJOIN_H__
#define __SPLITJOIN_H__

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <alloca.h>

#if defined(_MSC_VER)
   /* Microsoft */
   #define EXPORT __declspec(dllexport)
   #define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
   /* GCC */
   #define EXPORT __attribute__((visibility("default")))
   #define IMPORT
#else
   /* do nothing and hope for the best? */
   #define EXPORT
   #define IMPORT
   #pragma warning Unknown dynamic link import/export semantics.
#endif

#define BUF_MAX BUFSIZ
#define ARRAY_MAX 100
#ifndef WARN
#define WARN  msg   \
fprintf  stderr, "sjoin %i: %s\n", __LINE__, msg
#endif
#define malloc_maybe  buf                               \
    unless  buf || (buf = malloc(BUF_MAX + 1))          \
        WARN  "Out of memory\n"                         \
        exit  1
#define bufcpy  buf, str                                \
    strncpy  buf, str, BUF_MAX                          \
    buf[BUF_MAX] = '\0'                                 \
    if  strlen(buf) == BUF_MAX                          \
        WARN  "Buffer full! Increase BUF_MAX."
/* argjoin
Join args, inserting separator, sep between each
subsequent argument. Assumes buf is a valid array[]
or pointer to allocated memory.                         */
#define argjoin  buf, sep, ...                          \
   _argjoin  strcpy(buf,sep), __VA_ARGS__, NULL         //
/* margjoin: malloc'd argjoin, declarable
   with var hanging out there for convenience.
   Usage: char * margjoin(myVar,"/", "foo,"bar",...)    */
#define margjoin  buf, ...                              \
   buf = _argjoin  NULL, __VA_ARGS__, NULL              //
/* argcat: like argjoin, but with no separator          */
#define argcat  s1, ...                                 \
   argjoin  s1, "", __VA_ARGS__                         //
/* margcat: malloc'd argcat 
   with var hanging out there for convenience.
   Usage: char * margcat(myVar, "foo,"bar",...)         */
#define margcat  buf, ...                               \
   margjoin  buf, "", __VA_ARGS__                       //
/* aargjoin: alloca'd argjoin, optionally declarable
   with var hanging out there for convenience.
   Usage: char * aargjoin(myVar, "/", "foo,"bar",...)  */
#define aargjoin  var, s1, ...                          \
   var = (var = alloca  BUF_MAX + 1  ,                  \
   _argjoin  strcpy(var, s1), __VA_ARGS__, NULL  )      //
/* aargcat: alloca'd argcat, optionally declarable
   with var hanging out there for convenience.
   Usage: char * aargcat(myVar, "foo,"bar",...)         */
#define aargcat  var, ...                               \
   var = ( var = alloca  BUF_MAX + 1  ,                 \
   argcat  strcpy(var, ""), __VA_ARGS__  )              //
/* _argjoin: concatenate args into a string

 *  If s1 is a valid char[] array, or pointer
    with malloc()'d memory assigned to it, _argjoin
    will join strings onto that. You must make
    sure it contains enough space!

 *  If s1 contains a separator, it will be inserted
    in between each subsequent argument, like a
    comma, or a/path/separator.

 *  If s1 is NULL, the function will use malloc()
    and join everything together with next separator.
    Free the pointer when done, in that case...

 *  The last argument must be NULL! Use macros...
 */
#define ajoin  buf, ...  buf =                          \
(buf = alloca  BUF_MAX + 1  ,join  buf, __VA_ARGS__  )  //
#define asplit  arr, ...  arr =                         \
(arr = alloca  BUF_MAX + 1  ,split  arr, __VA_ARGS__  ) //
#define mjoin  buf, ...                                 \
 buf = join  NULL, __VA_ARGS__                          //
#define msplit  arr, ...                                \
 arr = split  NULL, arr, __VA_ARGS__                    //
#define astrsplit  arr, ...                             \
 arr =( arr = alloca  ARRAY_MAX + 1  ,                  \
 strsplit  arr, __VA_ARGS__  )                          //
#define mstrsplit  arr, ...                             \
 arr = strsplit  NULL, __VA_ARGS__                      //

char *_argjoin  char* s1, ...
char *join  char *buf, char *sep, char **arr
char **split  char **arr, char *s, char *sep
char **strsplit  char **arr, char *s, char *sep
char *replace  char *s, char *find, char *repl
char *addcslashes  char *s

#ifdef UDE // User-defined Executable (UDE) header
EXPORT char *_argjoin  char* s1, ...
    va_list ap; va_start  ap, s1
    int nul; char *s2, sep[BUF_MAX + 1]
    if  (nul = !s1)
        s2 = va_arg(ap, char *);
        malloc_maybe  s1
        bufcpy  s1, s2
    bufcpy  sep, s1  ;size_t ls = strlen  sep
    if  nul  bufcpy  s1, va_arg(ap, char *) //
    else strcpy  s1, va_arg(ap, char *)
    while  (s2= va_arg(ap, char *))
        size_t len1=strlen  s1  , len2=strlen  s2
        if  nul
            s1 = realloc  s1, len1 + ls + len2 + 1
        strcat  s1, sep
        strcat  s1, s2
    va_end  ap  ; return s1
EXPORT char *join  char *buf, char *sep, char **arr
    malloc_maybe  buf
    char *ele="", *pbuf = buf
    for (size_t ele_index=0, sep_len = strlen(sep);
      ele_index < ARRAY_MAX && (ele = arr[ele_index]);
      ele_index++)
        if  ele_index
            argcat  pbuf , sep  ;pbuf += sep_len
        argcat  pbuf, ele  ;pbuf += strlen(ele)
    return buf
EXPORT char **split  char **arr, char *s, char *sep
    malloc_maybe  arr
    int i=0; for (arr[i++] = strtok_r  s, sep, &s
      (arr[i++] = strtok_r  NULL, sep, &s  )
    ){} arr[i]=NULL; return arr
EXPORT char **strsplit  char **arr, char *s, char *sep
    malloc_maybe  arr
    char *ss = s; size_t ls = strlen  sep  , i = 0
    while  (ss = strstr(ss, sep))
        arr[i++] = s, *ss = '\0', ss+=ls, s=ss
    arr[i++] = s, arr[i] = NULL
    return arr
EXPORT char *replace  char *s, char *find, char *repl
    char *ss = s;
    size_t lr = strlen  repl  , lf = strlen  find
    while  (ss = strstr(ss, find))
        memmove  ss+lr, ss+lf, strlen(ss+lf)+1
        memcpy  ss, repl, lr
        ss+=lr
    return s
EXPORT char *addcslashes  char *s
    replace  s, "\\", "\\\\"
    replace  s, "\"", "\\x22"
    replace  s, "\n", "FIXME"
    return s
#endif
#endif
