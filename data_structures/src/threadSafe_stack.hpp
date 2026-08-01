#pragma once

#include <stack>
#include <memory>
#include <mutex>
#include <exception>

/**

- Thread safety is provided by protectitng each member function with a on the mutex m, ensuring that only one
thread is accessing the data at any time. No thread can see a broken invariant.


 */


struct empty_stack: std::exception{
    const char* what() const throw() override { return "empty stack"; }
};

template <typename T>
class ThreadSafeStack{
private:
    std::stack<T> data;
    mutable std::mutex mtx;

public:

    ThreadSafeStack() {}
    ThreadSafeStack (const ThreadSafeStack& other) {
        std::lock_guard<std::mutex> lock(other.mtx);
        data = other.data;
    }

    void push(T new_value){
        std::lock_guard<std::mutex> lock(mtx);
        data.push(std::move(new_value));
    }

    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(mtx);
        if (data.empty()) throw empty_stack();
        auto res = (std::make_shared<T>(std::move(data.top())));
        data.pop();
        return res;
    }

    void pop(T& value){
        std::lock_guard<std::mutex> lock(mtx);
        if (data.empty()) throw empty_stack();
        value = std::move(data.top());
        data.pop();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mtx);
        return data.empty();
    }
};