#include <gtest/gtest.h>
#include "threadSafe_list.hpp"
#include <atomic>
#include <thread>
#include <vector>

using data_structure::ThreadSafeList;

// --- Single-threaded correctness ---

TEST(ThreadSafeListTest, ForEachOnEmptyListVisitsNothing) {
    ThreadSafeList<int> list;
    int count = 0;
    
    list.for_each([&count](const int&) { ++count; });
    EXPECT_EQ(count, 0);
}

TEST(ThreadSafeListTest, PushFrontThenForEachVisitsMostRecentFirst) {
    ThreadSafeList<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);

    std::vector<int> visited;
    list.for_each([&visited](const int& v) { visited.push_back(v); });
    EXPECT_EQ(visited, (std::vector<int>{3, 2, 1}));
}

TEST(ThreadSafeListTest, FindFirstIfReturnsMatchingElement) {
    ThreadSafeList<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);

    auto found = list.find_first_if([](const int& v) { return v == 2; });
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(*found, 2);
}

TEST(ThreadSafeListTest, FindFirstIfOnMissReturnsNullptr) {
    ThreadSafeList<int> list;
    list.push_front(1);

    auto found = list.find_first_if([](const int& v) { return v == 99; });
    EXPECT_EQ(found, nullptr);
}

TEST(ThreadSafeListTest, RemoveIfDropsMatchingElements) {
    ThreadSafeList<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_front(4);

    list.remove_if([](const int& v) { return v % 2 == 0; });

    std::vector<int> remaining;
    list.for_each([&remaining](const int& v) { remaining.push_back(v); });
    EXPECT_EQ(remaining, (std::vector<int>{3, 1}));
}

TEST(ThreadSafeListTest, RemoveIfNoMatchLeavesListUnchanged) {
    ThreadSafeList<int> list;
    list.push_front(1);
    list.push_front(2);

    list.remove_if([](const int& v) { return v > 100; });

    std::vector<int> remaining;
    list.for_each([&remaining](const int& v) { remaining.push_back(v); });
    EXPECT_EQ(remaining, (std::vector<int>{2, 1}));
}

TEST(ThreadSafeListTest, DestructorOnNonEmptyListDoesNotCrash) {
    ThreadSafeList<int> list;
    for (int i = 0; i < 100; ++i) list.push_front(i);
    // list goes out of scope here — should tear down all 100 nodes cleanly
}

// --- Concurrent correctness ---

TEST(ThreadSafeListTest, ConcurrentPushFrontAllItemsVisible) {
    constexpr int THREADS = 8;
    constexpr int PER_THREAD = 200;
    ThreadSafeList<int> list;

    std::vector<std::thread> pushers;
    for (int t = 0; t < THREADS; ++t)
        pushers.emplace_back([&list] {
            for (int i = 0; i < PER_THREAD; ++i) list.push_front(1);
        });
    for (auto& p : pushers) p.join();

    std::atomic<int> count{0};
    list.for_each([&count](const int&) { count.fetch_add(1); });
    EXPECT_EQ(count.load(), THREADS * PER_THREAD);
}
