#ifndef UP_TIME_H_
#define UP_TIME_H_

#include <string>
#include <chrono>

namespace utiles
{
class UP_Time{
public:
    UP_Time();
    static UP_Time Now();
    std::string asString(const std::string& format = "%F %T") const;
    
    // Arithmetic operations
    template <typename Duration>
    UP_Time operator+(const Duration& duration) const;

    template <typename Duration>
    UP_Time operator-(const Duration& duration) const;
    
private:
    std::chrono::system_clock::time_point timePoint;
};
} // namespace utiles

#endif  // UP_TIME_H_