#include <gtest/gtest.h>
#include "threadSafe_lookupTable.hpp"
#include <string>
#include <thread>
#include <vector>

using data_structure::threadsafe_lookup_table;

// --- Single-threaded correctness ---

TEST(ThreadSafeLookupTableTest, AddOnExistingKeyUpdatesValue) {
    threadsafe_lookup_table<int, std::string> table;
    table.add_or_update_mapping(1, "one");
    table.add_or_update_mapping(1, "uno");
    table.add_or_update_mapping(2, "two");

    EXPECT_EQ(table.value_for(1, "missing"), "uno");
    EXPECT_EQ(table.value_for(2, "missing"), "two");
}

// --- Concurrent correctness ---

TEST(ThreadSafeLookupTableTest, ConcurrentWritesToDistinctKeysAllVisible) {
    constexpr int THREADS = 8;
    constexpr int PER_THREAD = 200;
    threadsafe_lookup_table<int, int> table;

    std::vector<std::thread> writers;
    for (int t = 0; t < THREADS; ++t)
        writers.emplace_back([&table, t] {
            for (int i = 0; i < PER_THREAD; ++i) {
                int key = t * PER_THREAD + i;
                table.add_or_update_mapping(key, key);
            }
        });
    for (auto& w : writers) w.join();

    for (int key = 0; key < THREADS * PER_THREAD; ++key)
        EXPECT_EQ(table.value_for(key, -1), key);
}
