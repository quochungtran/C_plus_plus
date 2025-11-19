#include "gtest/gtest.h"
#include <sstream>

#include "stack_using_single_list.hpp"

using namespace data_structure;

class StackUsingSingleListTest: public::testing::Test{
protected:
    StackUsingSingleList<int> stk;

    void SetUp() override{
        stk.clear();
    }
    void TearDown() override{
        stk.clear();
    }
};

TEST_F(StackUsingSingleListTest, getSizeTest){
    EXPECT_EQ(stk.getSize(), 0);
}

TEST_F(StackUsingSingleListTest, emptyListTest){
    EXPECT_TRUE(stk.isEmpty());
}

TEST_F(StackUsingSingleListTest, pushListTest){
    stk.push(3);
    stk.push(12);
    int x = 100;
    stk.push(x);
    EXPECT_FALSE(stk.isEmpty());
    EXPECT_EQ(stk.getSize(), 3);
    EXPECT_EQ(stk.top(), 100);

    stk.pop();
    EXPECT_EQ(stk.getSize(), 2);
    EXPECT_EQ(stk.top(), 12);

    stk.clear();
    EXPECT_TRUE(stk.isEmpty());
}