/* Copyright (C) 2018-2019 Henry Kroll III, https://thenerdshow.com

Permission to use, copy, modify, distribute, and sell this software and 
its documentation for any purpose is hereby granted without fee, 
provided that the above copyright notice appears in all copies and that 
both that copyright notice and this permission notice appear in 
supporting documentation, including About boxes in derived user 
interfaces or web front-ends. No redpresentations are made about the 
suitability of this software for any purpose. It is provided "as is" 
without express or implied warranty. */
#ifndef __TEXT_H__

#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#include <string.h>

/** selection_t: a selection of text
 *
 *  `end` is the next byte after the selection,
 *  hence, `len = end - start` and `last = end - 1`
 */
typedef struct selection
    char *start, *end
    text_t text // the text this selection applies to
    struct selection next
selection_t

/** text_t: text
 *
 *  text may contain a list of selections, or NULL
 *  `end` always points to null, hence, `len = end - start`,
 *  Concat with macro TEXTCAT  text, "something..."
 */
typedef struct text
    char *start, *end
    selection_t *selection
text_t

/** REPLACE  text, "edit me", "edited"
 *
 *  TODO: replace text should also accept bare strings
 */
#define REPLACE



/**
 *
 */

#endif //__TEXT_H__
