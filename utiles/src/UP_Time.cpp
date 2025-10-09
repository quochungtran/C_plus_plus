#include "UP_Time.h"
#include <iostream>

namespace utiles {
UP_Time::UP_Time(): timePoint(std::chrono::system_clock::now()){};

UP_Time UP_Time::Now()
{
    return UP_Time();
}

std::string UP_Time::asString(const std::string& format) const{
    std::time_t timeT = std::chrono::system_clock::to_time_t(timePoint);
    std::tm local_tm  = *std::localtime(&timeT);

    char buffet[80];
    std::strftime(buffet, sizeof(buffet), format.c_str(), &local_tm);
    return std::string(buffet); 
}

template <typename Duration>
UP_Time UP_Time::operator+(const Duration& duration) const {
    UP_Time result;
    result.timePoint = timePoint + duration;
    return result;
}

template <typename Duration>
UP_Time UP_Time::operator-(const Duration& duration) const{
    UP_Time result;
    result.timePoint = timePoint - duration;
    return result; 
}
}