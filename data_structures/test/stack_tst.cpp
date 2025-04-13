#include "gtest/gtest.h"
#include "stack.hpp"
#include "node.hpp"
using namespace data_structure;

TEST(stackTest, empty_stk){
    stackK<int> stk;
    ASSERT_EQ(stk.isEmptyStack(), true);
}

TEST(stackTest, push_stk){
    stackK<int> stk;    
    stk.push(10);
    stk.push(12);
    EXPECT_EQ(stk.getSize(), 2);
}

TEST(stackTest, pop_stk){
    stackK<int> stk;
    stk.push(10);
    stk.push(20);
    EXPECT_EQ(stk.top(), 20);
    EXPECT_EQ(stk.getSize(), 2);

    stk.pop();
    EXPECT_EQ(stk.getSize(), 1);
}