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

UP_Time UP_Time::addSeconds(int second) const{
    UP_Time result;
    result.timePoint = timePoint + std::chrono::seconds(second);
    return result;
}

UP_Time UP_Time::addMinutes(int minutes) const
{
    return addSeconds(minutes*60);
}

UP_Time UP_Time::addHours(int hours) const{
    return addSeconds(hours*3600);
}
}

int main()
{
    using namespace utiles;
    UP_Time now = UP_Time::Now();
    std::cout << now.asString() << "\n";
    return 0;
}