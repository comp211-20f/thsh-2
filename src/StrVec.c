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
    Vec_set(self, Vec_length(self), &value);
}

Str StrVec_pop(StrVec *self)
{
    Str s;
    size_t index = Vec_length(self) - 1;
    Vec_get(self, index, &s);
    Vec_splice(self, index, 1, NULL, 0);
    return s;
}

void StrVec_set(StrVec *self, size_t index, const Str value)
{
    if (index < Vec_length(self)) {
        Str *s = StrVec_ref(self, index);
        Str_drop(s);
    }
    Vec_set(self, index, &value);
}

void StrVec_drop(StrVec *self)
{
    while (!StrVec_empty(self)) {
        Str s = StrVec_pop(self);
        Str_drop(&s);
    }
    Vec_drop(self);
}

