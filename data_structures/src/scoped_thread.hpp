#pragma once
#include <thread>
#include <stdexcept>

class scoped_thread {
private:
    std::thread t_;

public:
    scoped_thread(std::thread iThread): t_(std::move(iThread)){
        if (!t_.joinable()){
            throw std::logic_error("No thread");
        }
    }

    ~scoped_thread() { if (t_.joinable()) t_.join(); }

    scoped_thread(const scoped_thread&) = delete;
    
    scoped_thread& operator=(const scoped_thread&) = delete;

    scoped_thread(scoped_thread&&) = default;

    scoped_thread& operator=(scoped_thread&&) = default;
};