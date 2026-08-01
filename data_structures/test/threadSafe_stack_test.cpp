#include <gtest/gtest.h>
#include "threadSafe_stack.hpp"
#include <thread>
#include <vector>
#include <atomic>

// --- Single-threaded correctness ---

TEST(ThreadSafeStackTest, EmptyAfterConstruction) {
    ThreadSafeStack<int> s;
    EXPECT_TRUE(s.empty());
}

TEST(ThreadSafeStackTest, NotEmptyAfterPush) {
    ThreadSafeStack<int> s;
    s.push(1);
    EXPECT_FALSE(s.empty());
}

TEST(ThreadSafeStackTest, PushAndPopSharedPtr) {
    ThreadSafeStack<int> s;
    s.push(42);
    auto ptr = s.pop();
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, 42);
}

TEST(ThreadSafeStackTest, PushAndPopRef) {
    ThreadSafeStack<int> s;
    s.push(7);
    int val = 0;
    s.pop(val);
    EXPECT_EQ(val, 7);
}

TEST(ThreadSafeStackTest, LIFOOrdering) {
    ThreadSafeStack<int> s;
    for (int i = 0; i < 5; ++i) s.push(i);
    for (int i = 4; i >= 0; --i) {
        auto ptr = s.pop();
        ASSERT_NE(ptr, nullptr);
        EXPECT_EQ(*ptr, i);
    }
}

TEST(ThreadSafeStackTest, EmptyAfterDraining) {
    ThreadSafeStack<int> s;
    s.push(1);
    auto ptr = s.pop();
    EXPECT_TRUE(s.empty());
}

TEST(ThreadSafeStackTest, PopSharedPtrOnEmptyThrows) {
    ThreadSafeStack<int> s;
    EXPECT_THROW(s.pop(), empty_stack);
}

TEST(ThreadSafeStackTest, PopRefOnEmptyThrows) {
    ThreadSafeStack<int> s;
    int val = 0;
    EXPECT_THROW(s.pop(val), empty_stack);
}

TEST(ThreadSafeStackTest, CopyConstructor) {
    ThreadSafeStack<int> original;
    original.push(10);
    original.push(20);

    ThreadSafeStack<int> copy(original);

    auto v1 = copy.pop();
    auto v2 = copy.pop();
    ASSERT_NE(v1, nullptr);
    ASSERT_NE(v2, nullptr);
    EXPECT_EQ(*v1, 20);
    EXPECT_EQ(*v2, 10);
    // original is unaffected
    EXPECT_FALSE(original.empty());
}

// --- Concurrent correctness ---

TEST(ThreadSafeStackTest, ConcurrentPushAllItemsConsumed) {
    constexpr int N = 1000;
    ThreadSafeStack<int> s;
    std::atomic<int> sum{0};
    std::atomic<int> received{0};

    std::thread producer([&] {
        for (int i = 1; i <= N; ++i) s.push(i);
    });

    std::thread consumer([&] {
        while (received.load() < N) {
            try {
                auto val = s.pop();
                sum += *val;
                ++received;
            } catch (const empty_stack&) {
                // stack momentarily empty, retry
            }
        }
    });

    producer.join();
    consumer.join();

    EXPECT_EQ(sum.load(), N * (N + 1) / 2);
}

TEST(ThreadSafeStackTest, MultipleProducersMultipleConsumers) {
    constexpr int PRODUCERS = 4;
    constexpr int PER_PRODUCER = 250;
    constexpr int TOTAL = PRODUCERS * PER_PRODUCER;

    ThreadSafeStack<int> s;

    // Phase 1: all producers push, then join — stack is fully populated before consumers start
    std::vector<std::thread> producers;
    for (int p = 0; p < PRODUCERS; ++p)
        producers.emplace_back([&s] {
            for (int i = 0; i < PER_PRODUCER; ++i) s.push(1);
        });
    for (auto& t : producers) t.join();

    // Phase 2: consumers drain the now-static stack; empty_stack signals completion
    std::atomic<int> sum{0};
    std::vector<std::thread> consumers;
    for (int c = 0; c < PRODUCERS; ++c)
        consumers.emplace_back([&] {
            while (true) {
                try {
                    auto val = s.pop();
                    sum.fetch_add(*val);
                } catch (const empty_stack&) {
                    break;
                }
            }
        });
    for (auto& t : consumers) t.join();

    EXPECT_EQ(sum.load(), TOTAL);
}

TEST(ThreadSafeStackTest, ConcurrentPushOnlyNoDataLoss) {
    constexpr int THREADS = 8;
    constexpr int PER_THREAD = 500;
    ThreadSafeStack<int> s;

    std::vector<std::thread> pushers;
    for (int t = 0; t < THREADS; ++t)
        pushers.emplace_back([&s] {
            for (int i = 0; i < PER_THREAD; ++i) s.push(i);
        });
    for (auto& t : pushers) t.join();

    int count = 0;
    while (!s.empty()) {
        s.pop();
        ++count;
    }
    EXPECT_EQ(count, THREADS * PER_THREAD);
}
