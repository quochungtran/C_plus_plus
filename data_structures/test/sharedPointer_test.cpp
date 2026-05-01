#include "gtest/gtest.h"
#include <sstream>

#include "sharedPointer.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <atomic>

using namespace data_structure;

TEST(SharedPointerTest, DefaultConstructorIsEmpty) {
    SharedPointer<int> p;
    EXPECT_EQ(p.get(), nullptr);
    EXPECT_EQ(p.use_count(), 0);
};

TEST(SharedPointerTest, NullptrConstructionIsSafe) {
    SharedPointer<int> p(nullptr);
    EXPECT_EQ(p.get(), nullptr);
    EXPECT_EQ(p.use_count(), 0);
}

TEST(SharedPointerTest, FromRawPointer) {
    SharedPointer<int> p(new int(42));
    EXPECT_NE(p.get(), nullptr);
    EXPECT_EQ(*p.get(), 42);
    EXPECT_EQ(p.use_count(), 1);

    auto p_str = make_shared<std::string>("hello");
    EXPECT_EQ(*p_str, "hello");
    EXPECT_EQ(p_str.use_count(), 1);
}

TEST(SharedPointerTest, FromNullptr) {
    SharedPointer<int> p(nullptr);
    EXPECT_EQ(p.get(), nullptr);
    EXPECT_EQ(p.use_count(), 0);
}

// Suite 2 — Reference counting

TEST(SharedPointerTest, RefCountCopyIncrementsCount) {
    auto a = make_shared<int>(1);
    auto b = a;
    EXPECT_EQ(a.use_count(), 2);
    EXPECT_EQ(b.use_count(), 2);
}

TEST(SharedPointerTest, RefCountThreeCopiesCountIsThree) {
    auto a = make_shared<int>(1);
    auto b = a;
    auto c = a;
    EXPECT_EQ(a.use_count(), 3);
    EXPECT_EQ(b.use_count(), 3);
    EXPECT_EQ(c.use_count(), 3);
}

TEST(SharedPointerTest, RefCountDestroyingCopyDecrements) {
    auto a = make_shared<int>(1);
    {
        auto b = a;
        EXPECT_EQ(a.use_count(), 2);
    }   // b destroyed here
    EXPECT_EQ(a.use_count(), 1);
}

// Copy semantics 
TEST(SharedPointerTest, CopyAssignmentSelfIsNoop){
    auto a = make_shared<int>(7);
    a = a;
    EXPECT_EQ(*a, 7);
    EXPECT_EQ(a.use_count(), 1);
}