#include "vector.hpp"
#include "gtest/gtest.h"

using namespace data_structure;

TEST(VectorTest, InitVector){
    Vector vec = Vector(3, 1);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
}

TEST(VectorTest, pushBackVector){
    Vector vec = Vector(3, 1);
    vec.push_back(2);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec[3], 2);
    EXPECT_EQ(vec.capacity(), 6);
}