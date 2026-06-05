#include "linked_stack.hpp"
#include "gtest/gtest.h"

using namespace data_structure;

TEST(LinkedStackTest, IsEmptyOnConstruct) {
    LinkedStack<int> s;
    EXPECT_TRUE(s.isEmpty());
    EXPECT_EQ(s.getSize(), 0u);
}

TEST(LinkedStackTest, PushAndTop) {
    LinkedStack<int> s;
    s.push(10);
    s.push(20);
    EXPECT_EQ(s.top(), 20);
    EXPECT_EQ(s.getSize(), 2u);
}

TEST(LinkedStackTest, PopReturnsLIFO) {
    LinkedStack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    EXPECT_EQ(s.pop(), 3);
    EXPECT_EQ(s.pop(), 2);
    EXPECT_EQ(s.pop(), 1);
    EXPECT_TRUE(s.isEmpty());
}

TEST(LinkedStackTest, PopOnEmptyThrows) {
    LinkedStack<int> s;
    EXPECT_THROW(s.pop(), std::underflow_error);
}

TEST(LinkedStackTest, TopOnEmptyThrows) {
    LinkedStack<int> s;
    EXPECT_THROW(s.top(), std::underflow_error);
}

TEST(LinkedStackTest, Clear) {
    LinkedStack<int> s;
    s.push(1);
    s.push(2);
    s.clear();
    EXPECT_TRUE(s.isEmpty());
    EXPECT_EQ(s.getSize(), 0u);
}

TEST(LinkedStackTest, PushRvalue) {
    LinkedStack<std::string> s;
    std::string word = "hello";
    s.push(std::move(word));
    EXPECT_EQ(s.top(), "hello");
}
