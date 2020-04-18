#include "gtest/gtest.h"

extern "C" {
#include "StrVec.h"
}

TEST(StrVecSpec, empty)
{
    StrVec sv = StrVec_value(10);
    ASSERT_EQ(0, StrVec_length(&sv));
    StrVec_drop(&sv);
}

TEST(StrVecSpec, push_pop)
{
    StrVec sv = StrVec_value(10);
    ASSERT_EQ(0, StrVec_length(&sv));
    StrVec_push(&sv, Str_from("hello"));
    ASSERT_EQ(1, StrVec_length(&sv));
    StrVec_push(&sv, Str_from("world"));
    ASSERT_EQ(2, StrVec_length(&sv));
    StrVec_push(&sv, Str_from("!!!"));
    ASSERT_EQ(3, StrVec_length(&sv));

    Str top;
    top = StrVec_pop(&sv);
    ASSERT_EQ(2, StrVec_length(&sv));
    ASSERT_STREQ("!!!", Str_cstr(&top));
    Str_drop(&top);

    top = StrVec_pop(&sv);
    ASSERT_EQ(1, StrVec_length(&sv));
    ASSERT_STREQ("world", Str_cstr(&top));
    Str_drop(&top);
    
    top = StrVec_pop(&sv);
    ASSERT_EQ(0, StrVec_length(&sv));
    ASSERT_STREQ("hello", Str_cstr(&top));
    Str_drop(&top);

    StrVec_drop(&sv);
}

TEST(StrVecSpec, set_ref)
{
    Str *ref;
    StrVec sv = StrVec_value(0);
    ASSERT_EQ(0, StrVec_length(&sv));

    StrVec_set(&sv, 0, Str_from("hello"));
    ASSERT_EQ(1, StrVec_length(&sv));
    ref = StrVec_ref(&sv, 0);
    ASSERT_STREQ("hello", Str_cstr(ref));

    StrVec_set(&sv, 1, Str_from("world"));
    ASSERT_EQ(2, StrVec_length(&sv));
    ref = StrVec_ref(&sv, 1);
    ASSERT_STREQ("world", Str_cstr(ref));
    
    StrVec_set(&sv, 1, Str_from("universe"));
    ASSERT_EQ(2, StrVec_length(&sv));
    ref = StrVec_ref(&sv, 1);
    ASSERT_STREQ("universe", Str_cstr(ref));

    StrVec_drop(&sv);
}
