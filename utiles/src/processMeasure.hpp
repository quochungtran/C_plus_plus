#pragma once

#include <chrono>
#include <functional>
#include "logging.h"
#include "UP_Time.h"

namespace utiles {

template <typename TimeUnit>
class Timer {
public:
    template <typename Func, typename... Args>
    static auto measure(Func&& func, Args&&... args) {
        using namespace std::chrono;
        auto start = high_resolution_clock::now();
        auto result = std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
        auto end = high_resolution_clock::now();
        auto elapsed = duration_cast<TimeUnit>(end - start).count();
        LOG(LogLevel::INFO, "Execution time: " << elapsed);
        return result;
    }
};

} // namespace utiles
