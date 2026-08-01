#include <gtest/gtest.h>
#include "threadSafe_queue.hpp"
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>

// --- Single-threaded correctness ---

TEST(ThreadSafeQueueTest, PushAndTryPopRef) {
    ThreadSafeQueue<int> q;
    q.push(42);
    int val = 0;
    ASSERT_TRUE(q.try_pop(val));
    EXPECT_EQ(val, 42);
}

TEST(ThreadSafeQueueTest, PushAndTryPopSharedPtr) {
    ThreadSafeQueue<int> q;
    q.push(7);
    auto ptr = q.try_pop();
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, 7);
}

TEST(ThreadSafeQueueTest, TryPopEmptyReturnsFalse) {
    ThreadSafeQueue<int> q;
    int val = 0;
    EXPECT_FALSE(q.try_pop(val));
}

TEST(ThreadSafeQueueTest, TryPopEmptyReturnsNullptr) {
    ThreadSafeQueue<int> q;
    EXPECT_EQ(q.try_pop(), nullptr);
}

TEST(ThreadSafeQueueTest, EmptyAfterConstruction) {
    ThreadSafeQueue<int> q;
    EXPECT_TRUE(q.empty());
}

TEST(ThreadSafeQueueTest, NotEmptyAfterPush) {
    ThreadSafeQueue<int> q;
    q.push(1);
    EXPECT_FALSE(q.empty());
}

TEST(ThreadSafeQueueTest, FIFOOrdering) {
    ThreadSafeQueue<int> q;
    for (int i = 0; i < 5; ++i) q.push(i);
    for (int i = 0; i < 5; ++i) {
        int val = -1;
        ASSERT_TRUE(q.try_pop(val));
        EXPECT_EQ(val, i);
    }
}

TEST(ThreadSafeQueueTest, EmptyAfterDraining) {
    ThreadSafeQueue<int> q;
    q.push(1);
    int val;
    q.try_pop(val);
    EXPECT_TRUE(q.empty());
}

TEST(ThreadSafeQueueTest, CopyConstructor) {
    ThreadSafeQueue<int> original;
    original.push(10);
    original.push(20);

    ThreadSafeQueue<int> copy(original);

    int v1 = 0, v2 = 0;
    ASSERT_TRUE(copy.try_pop(v1));
    ASSERT_TRUE(copy.try_pop(v2));
    EXPECT_EQ(v1, 10);
    EXPECT_EQ(v2, 20);
    // original is unaffected
    EXPECT_FALSE(original.empty());
}

TEST(ThreadSafeQueueTest, WaitAndPopRef) {
    ThreadSafeQueue<int> q;
    q.push(99);
    int val = 0;
    q.wait_and_pop(val);
    EXPECT_EQ(val, 99);
}

TEST(ThreadSafeQueueTest, WaitAndPopSharedPtr) {
    ThreadSafeQueue<int> q;
    q.push(55);
    auto ptr = q.wait_and_pop();
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, 55);
}

// --- Concurrent correctness ---

TEST(ThreadSafeQueueTest, ConcurrentPushAllItemsConsumed) {
    constexpr int N = 1000;
    ThreadSafeQueue<int> q;
    std::atomic<int> sum{0};

    std::thread producer([&] {
        for (int i = 1; i <= N; ++i) q.push(i);
    });

    std::thread consumer([&] {
        int received = 0;
        while (received < N) {
            int val;
            if (q.try_pop(val)) {
                sum += val;
                ++received;
            }
        }
    });

    producer.join();
    consumer.join();

    EXPECT_EQ(sum.load(), N * (N + 1) / 2);
}

TEST(ThreadSafeQueueTest, WaitAndPopUnblocksOnPush) {
    ThreadSafeQueue<int> q;
    int result = 0;

    std::thread consumer([&] { q.wait_and_pop(result); });

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    q.push(123);
    consumer.join();

    EXPECT_EQ(result, 123);
}

TEST(ThreadSafeQueueTest, MultipleProducersMultipleConsumers) {
    constexpr int PRODUCERS = 4;
    constexpr int PER_PRODUCER = 250;
    constexpr int TOTAL = PRODUCERS * PER_PRODUCER;

    ThreadSafeQueue<int> q;

    // Phase 1: all producers push, then join — queue is fully populated before consumers start
    std::vector<std::thread> producers;
    for (int p = 0; p < PRODUCERS; ++p)
        producers.emplace_back([&q] {
            for (int i = 0; i < PER_PRODUCER; ++i) 
                q.push(1);
        });
    for (auto& t : producers) t.join();

    // Phase 2: consumers drain the now-static queue; try_pop returns false when empty
    std::atomic<int> sum{0};
    std::vector<std::thread> consumers;
    for (int c = 0; c < PRODUCERS; ++c)
        consumers.emplace_back([&] {
            int val;
            while (q.try_pop(val)) sum.fetch_add(val);
        });
    for (auto& t : consumers) t.join();

    EXPECT_EQ(sum.load(), TOTAL);
}
