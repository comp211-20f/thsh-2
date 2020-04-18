#ifndef SLICE_H
#define SLICE_H

#include <stdlib.h>
#include <stdbool.h>

#include "CharItr.h"
#include "Str.h"

/**
 * A Slice is a pointer to a bounded, continuous range of bytes
 * in a char array.
 *
 * A Slice does not own its buffer pointer and its lifetime
 * ends when its referent's lifetime ends.
 */
typedef struct Slice {
    const char *start;
    size_t length;
} Slice;

/* Constructor */

Slice Slice_value(const char *start, size_t length);

/* Accessors */

const char* Slice_start(const Slice *self);

size_t Slice_length(const Slice *self);

/* Methods */

/**
 * Get a CharItr value from a Slice. The CharItr's lifetime
 * ends when the lifetime of the referent of the Slice ends.
 */
CharItr Slice_get_CharItr(const Slice *self);

/**
 * Get a Str value from a Slice. The caller of this function
 * owns the returned Str value and is responsible for calling
 * Str_drop when it is done with it.
 */
Str Slice_get_Str(const Slice *self);

/*
 * Equality comparison versus a (null-terminated) c-string.
 */
bool Slice_equals_cstr(const Slice *self, const char *cstr);

#endif
