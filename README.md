# Concise, Regex-Aware Preprocessor (CRAP)
Yet another C (computer language) code decorator and language maker.

<img style="float:right" src="https://eyeopeners.design/emoticons/faces/emoticon_pile-of-poop.png">Brought to you by [TheNerdShow.com](http://thenerdshow.com).

## Let's give everyone crap for writing crappy code.

* **Terse**. Under 150 lines of pure, unadulterated crap.
* **Simple**. Write programs with a simplified syntax.
* **Compatible**. Won't break existing code unless it looks like crap.*
* **Extendable**. Drop in complex macros that would confuse any compiler.
* **Unencumbered**. Freedom enforced by Apache License.

## Crap. It's not a compiler. It's a movement.

Crap includes powerful macrotives to make coding sessions flow more smoothly. 
The easiest way to explain it is to show some examples.

The following crap-worthy example prints "hello world" five times.

```
#include <stdio.h>
main
    repeat  5
        puts  "hello"
```

After processing, it becomes more or less standard C.

```
#include <stdio.h>
int main(int argc, char **argv){
    for(size_t _=5;_--;){
        puts ("hello");
    return 0;
}
```

## This language is crap.

Yes, yes it is.

*Crap is in alpha stages of software development. Use at your own risk! In case 
the name isn't good enough, we make no guarantees about its fertilizer content 
or implied fitness for gardening. Have fun and experiment under the terms of the 
included LICENSE. For other, lucrative uses, please contact the author.

## This crap has limits.

Single lines are limited to 8000 characters (about 80 linebreaks on a 
100-character terminal). There is enough buffer space for perhaps 99 levels of 
indent. You can bump up the limits in "crap.h" at the expense of more memory 
usage, but why? It would be more prudent to break up long lines and put some of 
those indented blocks into separate functions.

## Crap rules.

Here are some flexible rules for turning crap into compatible C code.

*Includes.* As with C, programs should "#include <stdio.h>" if they want to 
print to, or read from, consoles or files in a standard way.

*Expand "main" and return*. The optional "main" macro, when it occurs all by 
itself, expands to "int main(int argc, char **argv)". Using "main" causes 
"return 0" to be appended, so make sure "main" is the last function in the file.

*Curly brackets (braces).* Braces magically appear around code blocks when they 
are indented by tabs or four spaces (the default, as defined in "crap.h"). 
Comments must be indented to the same level as code. To avoid automatic 
bracketing for style reasons, do not indent the full four spaces; indent two or 
three spaces instead. If, for some reason, a semicolon must appear after the 
automatic closing brace, then start the next line with one.

*Parenthesis.* Crap puts parenthesis around arguments in a linear fashion, if 
they are set off by two spaces. "while _ _ a == b _ _ puts _ _ c" is shorthand 
for "while(a == b) puts(c)". It is often preferable to put parenthesis around 
things manually, as with logical operators and "truth y" value assignments. Those 
who dislike the feature do not have to use it, but it persists for the author's 
convenience.

*Semicolons.* Added to every line, except the line above an indented block (like 
if, for or while), and lines that end with any of the characters 
"<>;,.=*/&|^!". Ending a line with one of those characters or a space permits 
long statements to be broken up across multiple lines.

*Return.* Again, crap adds a final "return 0" only when "main" is used.

## Spreading crap around.

Usage couldn't be simpler. There are no command options. Use standard shell 
pipes '|' to fling crap at compilers, or '>' to crap descreetly into a file.

```
# Let's make holy.c from holy.crap.
crap holy.crap > holy.c
```

## A legacy of crap.

Crap's predecessor, Anchor, is still remarkably stable. But don't look at the 
code! It abuses `flex` in horrible ways and is otherwise unmaintainable. To make 
matters worse, `flex` grinds through confusing modes of operation during 
parsing, tripping flags, and interpreting things differently as it goes.

Crap drops the `flex` dependency and implements its own simplified regex calls.

## Crapping for executives, using the three C shells.

Shell commands may be embedded into the first line to make executable scripts 
for rapid testing and development. The following comment at the top of the file 
tells the shell to use crap to pipe '|' generated C code to the tinycc compiler. 
The `-run` option tells `tcc` to execute the compiled code. A well-placed "exit 
0" prevents shells from attempting to execute the remaining crap as shell code.

```
//bin/crap "$0" |tcc -run - "$@";exit 0
```

You may use other compilers or shells. Get creative!

## Now we're just making crap up.

Crap works like any lexer, Vala, or C preprocessor. This `Makefile` target tells 
GNU `make` to turn `.crap` files into `.c` files as needed.

```
%.c : %.crap
    crap "$<" > "$@"
```

## Installing crap.

```
make
sudo make install
```

## Wipe, and start over.

```
make uninstall
make clean
```

## Using crap for "boot tracking."

Our privacy policy for crap strictly forbids tracking. Please scrub off and leave boots outside.

## Picking up fresh crap.

Didn't Mom warn you about playing with dirty old crap? Don't take crap from just 
anyone. Get a fresh pile from [https://github.com/themanyone/crap].

`git clone https://github.com/themanyone/crap.git`

Copyright (C) 2018-2019 Henry Kroll III, [https://thenerdshow.com]

Permission to use, copy, modify, distribute, and sell this software and its 
documentation for any purpose is hereby granted without fee, provided that the 
above copyright notice appears in all copies and that both that copyright notice 
and this permission notice appear in supporting documentation, including About 
boxes in derived user interfaces or web front-ends. No representations are made 
about the suitability of this software for any purpose. It is provided "as is" 
without express or implied warranty.
