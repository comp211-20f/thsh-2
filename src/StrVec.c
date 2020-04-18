#include <stdio.h>
#include "StrVec.h"

StrVec StrVec_value(size_t capacity)
{
    return Vec_value(capacity, sizeof(Str));
}

size_t StrVec_length(const StrVec *self)
{
    return Vec_length(self);
}

Str* StrVec_ref(const StrVec *self, size_t index)
{
    return Vec_ref(self, index);
}

bool StrVec_empty(const StrVec *self)
{
    return Vec_length(self) == 0;
}

void StrVec_push(StrVec *self, Str value)
{
    // TODO
}

Str StrVec_pop(StrVec *self)
{
    Str s = { 0 };
    // TODO
    return s;
}

void StrVec_set(StrVec *self, size_t index, const Str value)
{
    // TODO
}

void StrVec_drop(StrVec *self)
{
    // TODO
}

