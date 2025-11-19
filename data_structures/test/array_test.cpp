#include "array.hpp"
#include "gtest/gtest.h"

using namespace data_structure;

TEST(ArrayTest, InitArray){
    Array<int, 5> arr(3);
    EXPECT_EQ(arr[0], 3);
    arr[0] = 2;
    EXPECT_EQ(arr[0], 2);
}