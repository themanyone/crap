/* From http://www.robertgamble.net/2012/01/c11-generic-selections.html

This allows the creation of a macro that can print any type of value that printf 
supports without having to specify the type explicitly in the call: */

#ifndef __print_h
#define __print_h
#include <stdarg.h>

#define printf_dec_format(x) _Generic((x), \
    char: "%c", \
    signed char: "%hhd", \
    unsigned char: "%hhu", \
    signed short: "%hd", \
    unsigned short: "%hu", \
    signed int: "%d", \
    unsigned int: "%u", \
    long int: "%ld", \
    unsigned long int: "%lu", \
    long long int: "%lld", \
    unsigned long long int: "%llu", \
    float: "%f", \
    double: "%f", \
    long double: "%Lf", \
    char *: "%s", \
    void *: "%p")

#define print(x) printf(printf_dec_format(x), x), printf(" ")
#define println(x) printf(printf_dec_format(x), x), putchar('\n')

#if 0
// We can then print values like so:
    print('a');    // prints "97" (on an ASCII system)
    print((char)'a');  // prints "a"
    print(123);    // prints "123"
    print(1.234);      // prints "1.234000"
#endif
#endif
