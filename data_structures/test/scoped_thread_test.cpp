#include <gtest/gtest.h>
#include "scoped_thread.hpp"
#include <atomic>
#include <stdexcept>

TEST(ScopedThreadTest, AutoJoinsOnDestruction) {
    std::atomic<bool> ran{false};
    {
        scoped_thread st(std::thread([&] { ran = true; }));
    } // destructor joins here
    EXPECT_TRUE(ran);
}

TEST(ScopedThreadTest, ThrowsOnNonJoinableThread) {
    std::thread empty;
    EXPECT_THROW(scoped_thread st(std::move(empty)), std::logic_error);
}

TEST(ScopedThreadTest, MoveConstruct) {
    std::atomic<bool> ran{false};
    scoped_thread a(std::thread([&] { ran = true; }));
    scoped_thread b(std::move(a));
    // b joins on destruction
}
