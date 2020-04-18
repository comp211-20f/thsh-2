#include <stdio.h>

#include "CharItr.h"

CharItr CharItr_value(const char *start, size_t length)
{
    CharItr ci = {
        (char*) start,
        start + length
    };
    return ci;
}

CharItr CharItr_of_Str(const Str *str)
{
    return CharItr_value(Str_ref(str, 0), Str_length(str));
}

const char* CharItr_cursor(const CharItr *self)
{
    return self->cursor;
}

bool CharItr_has_next(const CharItr *self)
{
    return self->cursor < self->sentinel;
}

char CharItr_peek(const CharItr *self)
{
    if (CharItr_has_next(self)) {
        return *self->cursor;
    } else {
        fprintf(stderr, "%s:%d - Out of Bounds", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
}

char CharItr_next(CharItr *self) {
    if (CharItr_has_next(self)) {
        return *self->cursor++;
    } else {
        fprintf(stderr, "%s:%d - Out of Bounds", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
}
