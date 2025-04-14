#include "gtest/gtest.h"
#include <sstream>
#include "node.hpp"
#include "minHeap.hpp"

using namespace data_structure;

TEST(MinHeapTest, getSize){
    MinHeap<int> hp;
    EXPECT_EQ(hp.getSize(), 0);
}