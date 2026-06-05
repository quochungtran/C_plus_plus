#pragma once

#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

// Thread-safe queue from C++ Concurrency in Action, Ch.4 (Williams).
// All overloads are provided: blocking wait_and_pop and non-blocking try_pop.
template <typename T>
class ThreadSafeQueue {
    mutable std::mutex mut_;
    std::queue<T> queue_;
    std::condition_variable cond_;

public:
    ThreadSafeQueue() = default;

    ThreadSafeQueue(const ThreadSafeQueue& other) {
        std::lock_guard<std::mutex> lk(other.mut_);
        queue_ = other.queue_;
    }

    ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;

    void push(T value) {
        std::lock_guard<std::mutex> lk(mut_);
        queue_.push(std::move(value));
        cond_.notify_one();
    }

    // Blocks until an item is available, then moves it into value
    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lk(mut_);
        cond_.wait(lk, [this] { return !queue_.empty(); });
        value = std::move(queue_.front());
        queue_.pop();
    }

    // Blocks until an item is available, returns it via shared_ptr
    std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<std::mutex> lk(mut_);
        cond_.wait(lk, [this] { return !queue_.empty(); });
        auto res = std::make_shared<T>(std::move(queue_.front()));
        queue_.pop();
        return res;
    }

    // Non-blocking: returns false immediately if empty
    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lk(mut_);
        if (queue_.empty()) return false;
        value = std::move(queue_.front());
        queue_.pop();
        return true;
    }

    // Non-blocking: returns nullptr if empty
    std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> lk(mut_);
        if (queue_.empty()) return {};
        auto res = std::make_shared<T>(std::move(queue_.front()));
        queue_.pop();
        return res;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lk(mut_);
        return queue_.empty();
    }
};
