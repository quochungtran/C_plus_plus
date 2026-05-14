#pragma once

#include <iostream>
#include <sstream> // ostringstream
#include "UP_Time.h"

enum class LogLevel {DEBUG, INFO, WARNING, ERROR, CRITICAL};

#define LOG(level, msg) do { \
    std::ostringstream oss; \
    oss << msg; \
    utiles::Logger::log(level, oss.str()); \
} while(0)
namespace utiles{
class Logger {
public:
    static void log(LogLevel level, const std::string& iMessage);
};
}
