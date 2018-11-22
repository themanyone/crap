# Concise, Regex-Aware Preprocessor (CRAP)
C (computer language) extender for `crap` coders, toy language 
inventors.

<img style="float:right"
src="https://proxy.duckduckgo.com/iu/?u=http%3A%2F%2Ficons.iconarchive.com%2Ficons%2Fgoogle%2Fnoto-emoji-smileys%2F128%2F10104-pile-of-poo-icon.png&f=1">

## Giving everyone `crap` for writing crappy code.

* **Terse**. Under 200 lines of pure, unadulterated `crap`.
* **Simple**. Uses a simplified syntax `crap` coders can understand.
* **Compatible**. Won't break existing code unless it looks like `crap`.*
* **Extendable**. Build complex macros that would confuse any compiler.
* **Unencumbered**. Freedom enforced by BSD-style License.

## Crap. It's not a compiler. It's a movement.

Crap includes gentle macros to make coding sessions flow more 
smoothly. The easiest way to explain it is to show some examples.

The following crap-worthy example prints "hello world" five times.

```
#include <stdio.h>
main
    repeat  5
        puts  "hello world"
```

After processing, it becomes more or less standard C.

```
#include <stdio.h>
int main(int argc, char **argv, char** env){
    for(size_t _=5;_--;){
        puts ("hello world");
    return 0;
}
```

## This is `crap`.

Yes, yes it is.

*Crap is in alpha stages of development. Use at your own risk! In case 
the name isn't good enough, there are no guarantees about its 
fertilizer content or implied fitness for gardening. Have fun and 
experiment under the terms of the included LICENSE. For other, 
lucrative, uses please contact the author.

## Crap has `crap`ped itself!

Crap bootstrapped itself some time ago, so its source code is `crap`. As 
future development progresses in `crap` code, rest assured that `crap` will 
always remain 100% `crap`.

Generated C source files are included, so thankfully there is no 
prerequisite for `crap` to compile `crap`.

## Even `crap` has limits.

Single lines are limited to 8000 characters (about 80 line breaks on a 
100-character terminal). There is enough buffer space for perhaps 99 
levels of indent. You can bump up the limits in `crap.h` at the expense 
of more memory usage, but why? It is prudent to break up long lines and 
move overly-indented blocks into separate functions or libraries.

## Craptastic rules.

An extendable and growing set of rules turns `crap` code into C.

**Includes.** Like C, Crap programs `#include <stdio.h>` if they want to 
print to, or read from, consoles or files in a standard way. See 
`test2.crap` for a demo that uses `"asprintf.h"` for string and array 
manipulation.

**Expand `main` and return**. The optional `main` macro, when it occurs all 
by itself, expands to `int main(int argc, char **argv, char** env)`. Using 
`main` causes `return 0` to be appended, so make sure `main` is the last 
function in the file.

**Curly brackets (braces).** Braces magically appear around indented 
code blocks of four spaces or a tab (the default, as defined in 
`crap.h`). As a consequence, comments must be indented to the same 
level as code. To indent for style reasons, but skip automatic 
bracketing, do not indent the full four spaces; indent two or three 
spaces instead. If, for some reason, a semicolon must appear after the 
automatic closing brace, then start the next line with one.

**Parenthesis.** Crap puts parenthesis around arguments in a linear 
fashion, if they are set off by two spaces. `while _ _ a == b _ _ puts 
_ _ c` is shorthand for `while(a == b) puts(c)`. The convention works 
for most statements. It is often preferable to put parenthesis around 
things manually, as with logical operators and "truth y" value 
assignments. Those who dislike the feature do not have to use it, but 
it persists for the author's convenience.

**Semicolons.** Added to every line, except the line above the indented code 
block (probably if, for or while). If that line needs a semicolon for some 
reason, just add it manually. Other lines that do not receive a semicolon 
are preprocessor statements like `#define`, and lines that end with any of 
the characters ` <>;,."=*/&|^!`. Ending lines with one of those characters 
permits long statements to be broken up across multiple lines, without 
receiving unwanted semicolons.

**Return.** Again, `crap` adds a final `return 0` only when `main` is used. 
In other words, please supply functions with `return` values.

## `Crap` language extensions.

### Decisions.

**`unless`** Another way to write `if(!())`.

**`until`** Shorthand for while(!()).

### Pasted loops.

**`repeat`** The `repeat n[, mylabel]` constructor pastes a `for` loop into 
the code to repeat `n` times. A local `_index` variable is defined that may 
not be accessed outside the loop. An optional `mylabel` attribute causes 
`_index` to take on a unique name, `mylabel_index` so nested `repeat` loops 
are possible.

**`for mylabel in array[[start][:end]]`** Loops over `array`, assigning each 
element to the supplied, predefined variable (or pointer), in turn. An 
optional `start` and `end` may be preceded with a `-` sign, which means 
subtracted from the last element (calculated with `sizeof`, so negative indexes 
will not work with dynamic arrays). The `mylabel` and `array` labels help 
declare local unsigned variables, `mylabel_index` and `mylabel_end` which are 
not available outside the loop. Note that `mylabel_end` is 1 + the optional 
`[:end]` argument which, if supplied, will probably not be the real length of 
the array. If no optional `[:end]` is provided, `crap` will calculate 
`mylabel_end` using the `sizeof` operator, stepping through all remaining 
elements, including `NULL` or `undefined` elements. And finally, a non-negative 
`[:end]` must be supplied for dynamic (malloc'd) objects which are subject to 
change. How could `crap` calculate such things before compilation?

**`while mylabel in array[[start][:end]]`** *Exactly* like `for mylabel in 
array` but with an additional dereference to quit at the first sign of 
`NULL` data. Typically, a plain `while(*data)` statement is sufficient to 
loop through `NULL`-terminated arrays. But this extension inherits the safer 
end limits, indexing, and slight speed penalty, of the above `for` loop. 
Again, a non-negative `[:end]` is necessary for dynamic arrays to prevent 
out of bounds conditions.

**`array[[start]:[end]]`** This particular style of array notation drops in 
a code block that attempts to create a duplicate array, but with the same or 
fewer elements assigned to it. Trying to use `[start:end]` notation on the 
resulting array with negative and unspecified indexes will get results 
based on the old lengths, which might get confusing as the array gets passed 
around. `Crap` merely rearranges source code. The programmer is responsible 
for keeping track of runtime lengths and values!

Arrays may be initialized in a manner exactly like C: `int w[]={1,2,3,4,5}` or 
`char *s[]={"this","and","that"}`. The first array length does not need to be 
specified in the declaration.

**More `crap` examples** Our code pastes can walk through multidimensional 
arrays, but be sure to use the appropriate type declaration. In the 
following example, the first loop uses a pointer because it's returning a 
whole row. The inner loop, `j`, uses an `int` type because the innermost 
type of the 2D array, the one we want to print, is `int`.

```
    int test_image[M][N]=
     {{1,2,3,4},
      {5,6,7,8},
      {9,10,11,12}},

    *i, j

    for i in test_image
        for j in i[:4] // specify :4 here 'cause `i` could point to anything
            printf  "%i%s ", j, j_index==j_end-1?"\n":","
```

There is a handy program and website called [cdecl](https://cdecl.org/) that 
explains C's type declarations.

```
Array indexes start at [zero].
This array has 5 indexes, numbered 0 - 4.
  0 < 5: zero
  1 < 5: one
  2 < 5: two
  3 < 5: three
  4 < 5: four

Like Python, `:end` is 1-past the `last` element.
words[1:4] = { "one", "two", "three" }
words[ 2:] = { "two", "three", "four" }
words[ :3] = { "zero", "one", "two" }
words[ :-3] = { "zero", "one" }
words[ -3 : -1 ] = { "two", "three" }
```
### Embedded `crap` macros.

**Custom `crap`** Crap's `#replace /pattern/replacement/` macros support up 
to `\7` octal backref substitutions almost like `sed` scripts. They are no 
replacement for `sed`, nor do they supersede other preprocessor directives. 
But they could change things up. Up to 100 replacements per line, defined 
in `crap.h`. Rules may be added to `crap`'s source code for all users, or 
embedded into individual `crap` files where desired. Embedded `#replace` 
rules do not cross file boundaries, so do not put them in headers and 
expect them to work elsewhere.

**What isn't `crap`?** [The C programming language](http://c-faq.com/index.html). Compilers like the [Gnu C 
Compiler](https://gcc.gnu.org/) (GCC), [TinyCC](https://repo.or.cz/tinycc.git), 
most other free software. Mention of tools and technoligies is for information 
purposes and does not constitute endorsement or affiliation. `Sed`, `awk`, 
`perl`, and `grep` have more robust regex engines and are thoroughly tested, so 
use those instead of `crap` for handling arbitrary data streams.

## Spreading `crap` around.

Usage couldn't be simpler. There are no command options. Use standard shell 
pipes '|' to fling `crap` at compilers, or '>' to `crap` descreetly into a file.

```
# Let's make holy.c from holy.crap.
crap holy.crap > holy.c
```

## A legacy of `crap`.

Crap's predecessor, [Anchor](http://anch.org/anchor.html), is remarkably 
stable. But don't look at the code! It abused `flex` in horrible ways and 
was otherwise unmaintainable. To make matters worse, `flex` grinds through 
confusing modes of operation during parsing, tripping flags, and 
interpreting things differently as it goes.

Crap drops the `flex` dependency and implements its own simplified regex calls.

## Crapping for executives, using the three C shells.

Shell commands may be embedded into the first line to make executable scripts 
for rapid testing and development. The following comment at the top of the file 
tells the shell to use `crap` to pipe '|' generated C code to the tinycc compiler. 
The `-run` option tells `tcc` to execute the compiled code. A well-placed `exit 
0` prevents shells from attempting to execute the remaining `crap` as shell code.

```
//bin/crap "$0" |tcc -run - "$@";exit 0
```

You may use other compilers or shells. Get creative!

## Now we're just making `crap` up.

Crap works like any lexer, Vala, or C preprocessor. This `Makefile` target tells 
GNU `make` to turn `.crap` files into `.c` files as needed.

```
%.c : %.crap
    crap "$<" > "$@"
```

## Installing `crap`.

There is no `./configure` file. Edit the `Makefile` to change paths 
relevant to your system before running `make`. If the build complains 
about a missing library or header file, use the system package manager 
to find it or search the web. Developers, testers, and those who want 
to improve upon `crap`'s regex engine, or include it into other 
projects, may desire to `make shared` to build shared libraries.

```
make
sudo make install
```

## Wipe, and start over.

```
make uninstall
make clean
```

## Using `crap` for "boot tracking."

Our privacy policy for `crap` strictly forbids tracking. Please scrub off 
and leave boots outside.

Crap *does* include a tool for *boostrapping*, however. Developers 
tweaking our engine should use `make shared` and `bootstrap_test` to 
make sure everything works before installing untested `crap`.

## Picking up fresh `crap`.

Didn't Mom warn you about playing with dirty old `crap`? Don't take `crap` 
from just anyone. Get a fresh pile from 
[GitHub](https://github.com/themanyone/crap).

`git clone https://github.com/themanyone/crap.git`

Copyright (C) 2018-2019 Henry Kroll III, https://thenerdshow.com

Permission to use, copy, modify, distribute, and sell this software and its 
documentation for any purpose is hereby granted without fee, provided that the 
above copyright notice appears in all copies and that both that copyright notice 
and this permission notice appear in supporting documentation, including About 
boxes in derived user interfaces or web front-ends. No representations are made 
about the suitability of this software for any purpose. It is provided "as is" 
without express or implied warranty.

