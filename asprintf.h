#ifndef __ASPRINTF_H__
#define __ASPRINTF_H__

#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>

// TODO: iterators

// This should work for most array types
#define len(array) (sizeof array / sizeof array[0])

/** inline msprintf() macro
    * "returns" a pointer to allocated memory or NULL.
    * does not return number of characters written.
    * is safe to return from functions.
    * result must be free()'d after use. */
#define msprintf(s, ...) \
   s = (s = malloc(snprintf(NULL, 0, __VA_ARGS__)+1), \
   s? (sprintf(s, __VA_ARGS__), s)                    \
   : (fprintf(stderr, "msprintf: out of memory\n"), s))

/** inline asprintf() uses alloca(), inherits quirks.
 DO NOT
    * free() the pointer.
    * return the result from functions.
    * use this macro in function arguments. */
#define asprintf(s, ...) \
   s = (s = alloca(snprintf(NULL, 0, __VA_ARGS__)+1), \
   sprintf(s, __VA_ARGS__), s)

#endif //__ASPRINTF_H__
