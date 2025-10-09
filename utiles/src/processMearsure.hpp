#include <iostream>
#include <chrono>
#include <functional>
#include "logging.h"

#include "UP_Time.h"

namespace utiles
{

template <typename timeType>
class Timer {
public:
    template <typename Func, typename... Args>
    static auto measure(Func&& func, Args&&... args) {
        using namespace std::chrono;
        auto start = high_resolution_clock::now();        
        auto result = std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
        auto end = high_resolution_clock::now();
                
        long long elapsed = 0;
        elapsed = std::chrono::duration_cast<timeType>(end-start).count();
        LOG(LogLevel::INFO, "Execution Time " << elapsed);
        return result;
    }
};

} // namespace utiles
