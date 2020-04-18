#include <ctype.h>

#include "Scanner.h"

Scanner Scanner_value(CharItr char_itr)
{
    Token next = {
        END_TOKEN,
        Str_from("")
    };

    Scanner itr = {
        char_itr,
        next
    };

    return itr;
}

bool Scanner_has_next(const Scanner *self)
{
    return false;
}

Token Scanner_peek(const Scanner *self)
{
    Token next = { 0 };
    return next;
}

Token Scanner_next(Scanner *self)
{
    Token next = { 0 };
    return next;
}
