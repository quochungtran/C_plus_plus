#include "array.hpp"
#include "gtest/gtest.h"

using namespace data_structure;

TEST(ArrayTest, FillConstructor) {
    Array<int, 5> arr(3);
    EXPECT_EQ(arr.size(), 5u);
    EXPECT_EQ(arr[0], 3);
    EXPECT_EQ(arr[4], 3);
}

TEST(ArrayTest, DefaultConstructorIsEmpty) {
    Array<int, 5> arr;
    EXPECT_EQ(arr.size(), 0u);
    EXPECT_EQ(arr.capacity(), 5u);
}

TEST(ArrayTest, InsertAtFront) {
    Array<int, 5> arr;
    arr.insert(0, 10);
    arr.insert(0, 20);
    EXPECT_EQ(arr[0], 20);
    EXPECT_EQ(arr[1], 10);
    EXPECT_EQ(arr.size(), 2u);
}

TEST(ArrayTest, InsertAtBack) {
    Array<int, 5> arr;
    arr.insert(0, 1);
    arr.insert(1, 2);
    arr.insert(2, 3);
    EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, RemoveShiftsElements) {
    Array<int, 5> arr;
    arr.insert(0, 10);
    arr.insert(1, 20);
    arr.insert(2, 30);
    arr.remove(1);            // removes 20
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 30);   // 30 shifted left
    EXPECT_EQ(arr.size(), 2u);
}

TEST(ArrayTest, InsertThrowsWhenFull) {
    Array<int, 2> arr;
    arr.insert(0, 1);
    arr.insert(1, 2);
    EXPECT_THROW(arr.insert(2, 3), std::out_of_range);
}

TEST(ArrayTest, OutOfRangeThrows) {
    Array<int, 3> arr(0);
    EXPECT_THROW(arr[5], std::out_of_range);
}
