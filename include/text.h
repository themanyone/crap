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
typedef struct selection{
    char *start, *end;
    text_t text // the text this selection applies to
    struct selection next;}
selection_t;

/** text_t: text
 *
 *  text may contain a list of selections, or NULL
 *  `end` always points to null, hence, `len = end - start`,
 *  Concat with macro TEXTCAT(text, "something...")
 */
typedef struct text{
    char *start, *end;
    selection_t *selection;}
text_t;

/** REPLACE(text, "edit me", "edited");
 *
 *  TODO: replace text should also accept bare strings;
 */
#define REPLACE



/**
 *
 */

#endif 