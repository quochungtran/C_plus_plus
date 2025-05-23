#ifndef DATA_STRUCTURES_STACK_HPP_
#define DATA_STRUCTURES_STACK_HPP_

#include <string>
#include <chrono>

namespace utiles
{
class UP_Time{
public:
    UP_Time();
    static UP_Time Now();
    std::string asString(const std::string& format = "%F %T") const;

    UP_Time addSeconds(int seconds) const;
    UP_Time addMinutes(int minutes) const;
    UP_Time addHours(int hours) const;

private:
    std::chrono::system_clock::time_point timePoint;
};
} // namespace utiles

#endif  // DATA_STRUCTURES_STACK_HPP_