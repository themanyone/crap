#ifndef __ASPRINTF_H__
#define __ASPRINTF_H__

#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>

// iterators

// This should work for most array types
#define len(array) (sizeof array / sizeof array[0])

// msprintf() uses malloc().
// It returns a pointer to allocated memory or NULL.
// It does not return the number of characters written.
// The resulting pointer is safe to return from functions.
// Do not forget to free() it to prevent a memory leak!
#define msprintf(s, ...) \
   s = malloc(snprintf(NULL, 0, __VA_ARGS__)+1); \
   if(s) sprintf(s, __VA_ARGS__); \
   else fprintf(stderr, "msprintf: out of memory")

// asprintf() uses alloca().
// It returns a pointer to local stack space.
// Do not attempt to free or return the pointer.
#define asprintf(s, ...) \
   s = alloca(snprintf(NULL, 0, __VA_ARGS__)+1); \
   sprintf(s, __VA_ARGS__)

#endif //__ASPRINTF_H__
