#include <future>
#include <iostream>
#include <mutex>
#include <thread>

// Demo: std::async with launch::async policy.
// The task runs eagerly in a NEW thread; main continues concurrently.
// result.get() blocks until the result is ready (or returns immediately
// if the task already finished).
//
// NOTE on the mutex: a lock only protects a shared resource if EVERY
// thread that touches it locks the SAME mutex. Here both the async task
// AND main lock `cout_mtx` before writing to std::cout — otherwise their
// output would still interleave (locking only one side protects nothing).
int main() {
    std::mutex cout_mtx;

    auto result = std::async(std::launch::async, [&]() { 
        std::lock_guard<std::mutex> lk(cout_mtx);
        std::cout << "Running in thread: " << std::this_thread::get_id() << std::endl;
        return 42;
    });

    {
        // main must lock the SAME mutex to be mutually exclusive with the task
        std::lock_guard<std::mutex> lk(cout_mtx);
        std::cout << "Main:           " << std::this_thread::get_id() << std::endl;
    }

    int answer = result.get();  // May block or return immediately
    std::cout << "Answer:         " << answer << std::endl;

    return 0;
}
