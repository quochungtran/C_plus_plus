#pragma once

#include <thread>

// RAII wrapper that joins on destruction — the C++20 std::jthread does the same.
// Useful for understanding why jthread exists and what it replaces.
class joining_thread {
    std::thread t_;

public:
    joining_thread() noexcept = default;

    template<typename Callable, typename... Args>
    explicit joining_thread(Callable&& func, Args&&... args)
        : t_(std::forward<Callable>(func), std::forward<Args>(args)...) {}

    explicit joining_thread(std::thread t) noexcept : t_(std::move(t)) {}

    joining_thread(joining_thread&& other) noexcept : t_(std::move(other.t_)) {}

    joining_thread& operator=(joining_thread&& other) noexcept {
        if (joinable()) join();
        t_ = std::move(other.t_);
        return *this;
    }

    joining_thread& operator=(std::thread t) noexcept {
        if (joinable()) join();
        t_ = std::move(t);
        return *this;
    }

    // The destructor is what makes this class useful: no forget-to-join bugs
    ~joining_thread() {
        if (joinable()) join();
    }

    joining_thread(const joining_thread&) = delete;
    joining_thread& operator=(const joining_thread&) = delete;

    bool joinable() const { return t_.joinable(); }
    void join() { t_.join(); }
    void detach() { t_.detach(); }
    void swap(joining_thread& other) noexcept { t_.swap(other.t_); }
    std::thread::id get_id() const { return t_.get_id(); }
};
