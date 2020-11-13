#include "gtest/gtest.h"

extern "C" {
#include "stdint.h"
#include "Vec.h"
}

TEST(VecGrader, set_get_with_excess_capacity)
{
    Vec v = Vec_value(1, sizeof(char));
    ASSERT_EQ(0, Vec_length(&v));
    char a = 'a';
    Vec_set(&v, 0, &a);
    char a_copy;
    Vec_get(&v, 0, &a_copy);
    ASSERT_EQ(a, a_copy);
    ASSERT_EQ(1, Vec_length(&v));
    Vec_drop(&v);
}

TEST(VecGrader, set_get_with_dynamic_growth)
{
    Vec v = Vec_value(1, sizeof(size_t));
    ASSERT_EQ(0, Vec_length(&v));

    const size_t BOUNDS = 600000;
    for (size_t i = 0; i < BOUNDS; ++i) {
        Vec_set(&v, i, &i);
    }
    ASSERT_EQ(BOUNDS, Vec_length(&v));

    for (size_t i = 0; i < BOUNDS; ++i) {
        size_t j;
        Vec_get(&v, i, &j);
        ASSERT_EQ(i, j);
    }

    Vec_drop(&v);
}

TEST(VecGrader, equals_empty)
{
    Vec a = Vec_value(1, sizeof(size_t));
    Vec b = Vec_value(2, sizeof(size_t));
    ASSERT_TRUE(Vec_equals(&a, &b));
    Vec_drop(&b);
    Vec_drop(&a);
}

TEST(VecGrader, equals_1_item)
{
    Vec a = Vec_value(1, sizeof(size_t));
    Vec b = Vec_value(1, sizeof(size_t));
    size_t x = 211;
    Vec_set(&a, 0, &x);
    Vec_set(&b, 0, &x);
    ASSERT_TRUE(Vec_equals(&a, &b));

    x = 110;
    Vec_set(&b, 1, &x);
    ASSERT_FALSE(Vec_equals(&a, &b));

    Vec_drop(&b);
    Vec_drop(&a);
}

Vec fixture() {
    Vec v = Vec_value(4, sizeof(uint64_t));
    uint64_t x = 1;
    for (size_t i = 0; i < 32; ++i) {
        Vec_set(&v, i, &x);
        x *= 2;
    }
    return v;
}

TEST(VecGrader, equals_many_items)
{
    Vec a = fixture();
    Vec b = fixture();
    Vec c = fixture();
    uint64_t x = 311;
    Vec_set(&c, 2, &x);
    ASSERT_TRUE(Vec_equals(&a, &b));
    ASSERT_FALSE(Vec_equals(&a, &c));
    ASSERT_FALSE(Vec_equals(&b, &c));
    Vec_drop(&c);
    Vec_drop(&b);
    Vec_drop(&a);
}


Vec fixture_from_int16_t_array(int16_t *a, size_t length)
{
    Vec v = Vec_value(length, sizeof(int16_t));
    for (size_t i = 0; i < length; ++i) {
        Vec_set(&v, i, &a[i]);
    }
    return v;
}

void splice_test_helper(
        int16_t initial_items[],
        size_t initial_length,
        size_t index,
        size_t delete_count,
        int16_t items[],
        size_t insert_count,
        int16_t expect[],
        size_t expect_length
      )
{
    Vec v = fixture_from_int16_t_array(initial_items, initial_length);
    Vec_splice(&v, index, delete_count, items, insert_count);
    ASSERT_EQ(expect_length, Vec_length(&v));
    for (size_t i = 0; i < expect_length; ++i) {
        int16_t x;
        Vec_get(&v, i, &x);
        ASSERT_EQ(expect[i], x);
    }
    Vec_drop(&v);
}

TEST(VecGrader, splice_prepend) {
    int16_t initial[] = { 0, 10, 20, 30 };
    size_t index = 0;
    size_t delete_count = 0;
    int16_t items[] = { -20, -10 };
    size_t insert_count = 2;
    int16_t expect[] = { -20, -10, 0, 10, 20, 30 };

    splice_test_helper(
        initial,
        sizeof(initial) / sizeof(int16_t),
        index,
        delete_count,
        items,
        insert_count,
        expect,
        sizeof(expect) / sizeof(int16_t)
    );
}

TEST(VecGrader, splice_append) {
    int16_t initial[] = { 0, 10, 20, 30 };
    size_t index = 4;
    size_t delete_count = 0;
    int16_t items[] = { -20, -10 };
    size_t insert_count = 2;
    int16_t expect[] = { 0, 10, 20, 30, -20, -10 };

    splice_test_helper(
        initial,
        sizeof(initial) / sizeof(int16_t),
        index,
        delete_count,
        items,
        insert_count,
        expect,
        sizeof(expect) / sizeof(int16_t)
    );
}

TEST(VecGrader, splice_delete) {
    int16_t initial[] = { 0, 10, 20, 30 };
    size_t index = 1;
    size_t delete_count = 2;
    int16_t items[] = {};
    size_t insert_count = 0;
    int16_t expect[] = { 0, 30 };

    splice_test_helper(
        initial,
        sizeof(initial) / sizeof(int16_t),
        index,
        delete_count,
        items,
        insert_count,
        expect,
        sizeof(expect) / sizeof(int16_t)
    );
}

TEST(VecGrader, splice_insert) {
    int16_t initial[] = { 0, 10, 20, 30 };
    size_t index = 2;
    size_t delete_count = 0;
    int16_t items[] = { -20, -10 };
    size_t insert_count = 2;
    int16_t expect[] = { 0, 10, -20, -10, 20, 30 };

    splice_test_helper(
        initial,
        sizeof(initial) / sizeof(int16_t),
        index,
        delete_count,
        items,
        insert_count,
        expect,
        sizeof(expect) / sizeof(int16_t)
    );
}

TEST(VecGrader, splice_replace_same) {
    int16_t initial[] = { 0, 10, 20, 30 };
    size_t index = 2;
    size_t delete_count = 2;
    int16_t items[] = { -20, -10 };
    size_t insert_count = 2;
    int16_t expect[] = { 0, 10, -20, -10 };

    splice_test_helper(
        initial,
        sizeof(initial) / sizeof(int16_t),
        index,
        delete_count,
        items,
        insert_count,
        expect,
        sizeof(expect) / sizeof(int16_t)
    );
}

TEST(VecGrader, splice_replace_longer_delete) {
    int16_t initial[] = { 0, 10, 20, 30 };
    size_t index = 1;
    size_t delete_count = 3;
    int16_t items[] = { -20, -10 };
    size_t insert_count = 2;
    int16_t expect[] = { 0, -20, -10 };

    splice_test_helper(
        initial,
        sizeof(initial) / sizeof(int16_t),
        index,
        delete_count,
        items,
        insert_count,
        expect,
        sizeof(expect) / sizeof(int16_t)
    );
}

TEST(VecGrader, splice_replace_longer_insert) {
    int16_t initial[] = { 0, 10, 20, 30 };
    size_t index = 1;
    size_t delete_count = 1;
    int16_t items[] = { -20, -10 };
    size_t insert_count = 2;
    int16_t expect[] = { 0, -20, -10, 20, 30 };

    splice_test_helper(
        initial,
        sizeof(initial) / sizeof(int16_t),
        index,
        delete_count,
        items,
        insert_count,
        expect,
        sizeof(expect) / sizeof(int16_t)
    );
}

TEST(VecGrader, splice_insert_partial) {
    int16_t initial[] = { 0, 10, 20, 30 };
    size_t index = 2;
    size_t delete_count = 0;
    int16_t items[] = { -20, -10 };
    size_t insert_count = 1;
    int16_t expect[] = { 0, 10, -20, 20, 30 };

    splice_test_helper(
        initial,
        sizeof(initial) / sizeof(int16_t),
        index,
        delete_count,
        items,
        insert_count,
        expect,
        sizeof(expect) / sizeof(int16_t)
    );
}

// OUT OF BOUNDS TESTS
TEST(VecGrader, set_out_of_bounds_1) {
    Vec v = Vec_value(2, sizeof(double));
    double x = 211.0;
    ASSERT_DEATH({
       Vec_set(&v, 1, &x);
    }, ".*");
}

TEST(VecGrader, set_out_of_bounds_2) {
    Vec v = Vec_value(3, sizeof(double));
    double x = 211.0;
   Vec_set(&v, 0, &x);
    ASSERT_DEATH({
       Vec_set(&v, 2, &x);
    }, ".*");
}

TEST(VecGrader, get_out_of_bounds_1) {
    Vec v = Vec_value(1, sizeof(double));
    double x;
    ASSERT_DEATH({
        Vec_get(&v, 0, &x);
    }, ".*");
}

TEST(VecGrader, get_out_of_bounds_2) {
    Vec v = Vec_value(2, sizeof(double));
    double x = 211;
    Vec_set(&v, 0, &x);
    ASSERT_DEATH({
        Vec_get(&v, 1, &x);
    }, ".*");
}

TEST(VecGrader, splice_out_of_bounds_index) {
    int16_t initial[] = { 0, 10, 20, 30 };
    size_t index = 5;
    size_t delete_count = 0;
    int16_t items[] = { -20 };
    size_t insert_count = 1;
    int16_t expect[] = { }; // Expect Error
    ASSERT_DEATH({
        splice_test_helper(
            initial,
            sizeof(initial) / sizeof(int16_t),
            index,
            delete_count,
            items,
            insert_count,
            expect,
            sizeof(expect) / sizeof(int16_t)
        );
    }, ".*");
}

TEST(VecGrader, splice_out_of_bounds_delete) {
    int16_t initial[] = { 0, 10, 20, 30 };
    size_t index = 3;
    size_t delete_count = 2;
    int16_t items[] = { };
    size_t insert_count = 0;
    int16_t expect[] = { }; // Expect Error
    ASSERT_DEATH({
        splice_test_helper(
            initial,
            sizeof(initial) / sizeof(int16_t),
            index,
            delete_count,
            items,
            insert_count,
            expect,
            sizeof(expect) / sizeof(int16_t)
        );
    }, ".*");
}
