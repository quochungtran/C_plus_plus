#include "gtest/gtest.h"
#include "stack.hpp"
#include "node.hpp"
using namespace data_structure;

TEST(stackTest, test1){
    stackK<int> stk;
    ASSERT_EQ(stk.isEmptyStack(), true);
}