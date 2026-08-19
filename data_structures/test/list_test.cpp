#include "list.hpp"
#include "gtest/gtest.h"

#include <string>
#include <vector>

using namespace data_structure;

// --- Tests for what's implemented today ---

TEST(DoubleLinkedListTest, DefaultConstructorIsEmpty) {
    DoubleLinkedList<int> list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0u);
}

TEST(DoubleLinkedListTest, ClearOnEmptyListIsNoop) {
    DoubleLinkedList<int> list;
    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0u);
}

TEST(DoubleLinkedListTest, MoveConstructorFromEmptyList) {
    DoubleLinkedList<int> a;
    DoubleLinkedList<int> b(std::move(a));
    EXPECT_TRUE(b.empty());
    EXPECT_TRUE(a.empty());  // moved-from list left in valid, empty state
}

TEST(DoubleLinkedListTest, MoveAssignmentFromEmptyList) {
    DoubleLinkedList<int> a;
    DoubleLinkedList<int> b;
    b = std::move(a);
    EXPECT_TRUE(b.empty());
    EXPECT_TRUE(a.empty());
}

TEST(DoubleLinkedListTest, SelfMoveAssignmentIsSafe) {
    DoubleLinkedList<int> a;
    a = std::move(a);
    EXPECT_TRUE(a.empty());
}

// --- Iterator tests ---
// push_back/push_front don't exist yet, so build lists via insert(end(), value),
// which is equivalent to appending.

TEST(DoubleLinkedListIteratorTest, BeginEqualsEndOnEmptyList) {
    DoubleLinkedList<int> list;
    EXPECT_TRUE(list.begin() == list.end());
}

TEST(DoubleLinkedListIteratorTest, BeginNotEqualEndAfterInsert) {
    DoubleLinkedList<int> list;
    list.insert(list.end(), 1);
    EXPECT_TRUE(list.begin() != list.end());
}

TEST(DoubleLinkedListIteratorTest, DereferenceReturnsInsertedValue) {
    DoubleLinkedList<int> list;
    list.insert(list.end(), 42);
    EXPECT_EQ(*list.begin(), 42);
}

TEST(DoubleLinkedListIteratorTest, InsertAtEndAppendsInOrder) {
    DoubleLinkedList<int> list;
    list.insert(list.end(), 1);
    list.insert(list.end(), 2);
    list.insert(list.end(), 3);

    std::vector<int> collected;
    for (auto it = list.begin(); it != list.end(); ++it) {
        collected.push_back(*it);
    }
    EXPECT_EQ(collected, (std::vector<int>{1, 2, 3}));
}

TEST(DoubleLinkedListIteratorTest, InsertBeforeMiddleIteratorSplicesInPlace) {
    DoubleLinkedList<int> list;
    list.insert(list.end(), 1);
    auto posOf3 = list.insert(list.end(), 3);
    list.insert(posOf3, 2);  // insert 2 before the node holding 3

    std::vector<int> collected;
    for (auto it = list.begin(); it != list.end(); ++it) {
        collected.push_back(*it);
    }
    EXPECT_EQ(collected, (std::vector<int>{1, 2, 3}));
}

TEST(DoubleLinkedListIteratorTest, InsertReturnsIteratorToNewElement) {
    DoubleLinkedList<int> list;
    auto it = list.insert(list.end(), 99);
    EXPECT_EQ(*it, 99);
}

TEST(DoubleLinkedListIteratorTest, InsertRvalueOverload) {
    DoubleLinkedList<std::string> list;
    std::string word = "hello";
    list.insert(list.end(), std::move(word));
    EXPECT_EQ(*list.begin(), "hello");
    EXPECT_EQ(list.begin()->size(), 5u);
}

TEST(DoubleLinkedListIteratorTest, PreIncrementReturnsReferenceToSelf) {
    DoubleLinkedList<int> list;
    list.insert(list.end(), 1); //    1 end
    list.insert(list.end(), 2); // 1  2 end
    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
}

TEST(DoubleLinkedListIteratorTest, PreDecrementFromEndReachesLastElement) {
    DoubleLinkedList<int> list;
    list.insert(list.end(), 1);
    list.insert(list.end(), 2);
    list.insert(list.end(), 3);
    // 1 2 3 end
    auto it = list.end();
    --it;
    EXPECT_EQ(*it, 3);
}

TEST(DoubleLinkedListIteratorTest, IncrementThenDecrementReturnsToSameElement) {
    DoubleLinkedList<int> list;
    list.insert(list.end(), 1);
    list.insert(list.end(), 2);

    auto it = list.begin();
    ++it;
    --it;
    EXPECT_EQ(*it, 1);
    EXPECT_TRUE(it == list.begin());
}

// --- Tests for the not-yet-implemented std::list-style API ---
// Uncomment each block as you implement the corresponding method(s).
// Keep the #if 0 guard around anything not implemented yet so the
// rest of the test suite keeps compiling.
#if 0

TEST(DoubleLinkedListTest, PushBackIncreasesSize) {
    DoubleLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    EXPECT_EQ(list.size(), 2u);
    EXPECT_FALSE(list.empty());
}

TEST(DoubleLinkedListTest, PushFrontIncreasesSize) {
    DoubleLinkedList<int> list;
    list.push_front(1);
    list.push_front(2);
    EXPECT_EQ(list.size(), 2u);
}

TEST(DoubleLinkedListTest, FrontAndBackReflectInsertionOrder) {
    DoubleLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(DoubleLinkedListTest, PopBackRemovesLastElement) {
    DoubleLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.pop_back();
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(list.back(), 1);
}

TEST(DoubleLinkedListTest, PopFrontRemovesFirstElement) {
    DoubleLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.pop_front();
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(list.front(), 2);
}

TEST(DoubleLinkedListTest, ClearAfterPushesResetsToEmpty) {
    DoubleLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0u);
}

TEST(DoubleLinkedListTest, MoveConstructorStealsElements) {
    DoubleLinkedList<int> a;
    a.push_back(1);
    a.push_back(2);
    DoubleLinkedList<int> b(std::move(a));
    EXPECT_EQ(b.size(), 2u);
    EXPECT_EQ(b.front(), 1);
    EXPECT_TRUE(a.empty());
}

#endif  // not-yet-implemented API
