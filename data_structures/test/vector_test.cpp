#include "vector.hpp"
#include "gtest/gtest.h"

using namespace data_structure;

TEST(VectorTest, DefaultConstructor) {
    Vector<int> v;
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), 0u);
}

TEST(VectorTest, FillConstructor) {
    Vector<int> v(3, 1);
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[2], 1);
}

TEST(VectorTest, PushBackGrows) {
    Vector<int> v(3, 1);
    v.push_back(2);
    EXPECT_EQ(v.size(), 4u);
    EXPECT_EQ(v[3], 2);
    EXPECT_EQ(v.capacity(), 6u);
}

TEST(VectorTest, PushBackRvalue) {
    Vector<std::string> v;
    v.push_back(std::string("hello"));
    EXPECT_EQ(v[0], "hello");
}

TEST(VectorTest, CopyConstructorIsDeepCopy) {
    Vector<int> a(3, 42);
    Vector<int> b(a);
    b[0] = 99;
    EXPECT_EQ(a[0], 42);  // a is unaffected
    EXPECT_EQ(b[0], 99);
}

TEST(VectorTest, MoveConstructorStealsBuffer) {
    Vector<int> a(3, 7);
    Vector<int> b(std::move(a));
    EXPECT_EQ(b.size(), 3u);
    EXPECT_EQ(b[0], 7);
    EXPECT_EQ(a.size(), 0u);   // a is empty after move
}

TEST(VectorTest, AtThrowsOutOfRange) {
    Vector<int> v(2, 0);
    EXPECT_THROW(v.at(5), std::out_of_range);
}

TEST(VectorTest, ResizeDefaultInitializesNewElements) {
    Vector<int> v(2, 1);
    v.resize(5);
    EXPECT_EQ(v[4], 0);  // new elements value-initialized
}
