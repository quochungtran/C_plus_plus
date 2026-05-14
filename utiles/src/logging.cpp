#include <iostream>
#include <mutex>
#include "UP_Time.h"
#include "logging.h"

namespace {
    std::string levelToString (LogLevel level){
        switch (level)
        {
            case LogLevel::DEBUG:
                return "DEBUG"; 
            case LogLevel::INFO:
                return "INFO";
            case LogLevel::WARNING:
                return "WARNING";
            case LogLevel::ERROR:
                return "ERROR";
            case LogLevel::CRITICAL:
                return "CRITICAL";
            default:
                return "UNKNOWN";
        }
    }
}

namespace utiles {
void Logger::log(LogLevel level, const std::string& iMessage){
    static std::mutex log_mutex;
    std::ostringstream logEntry;
    logEntry << "[" << UP_Time::Now().asString() << "] "
             << levelToString(level) << ": " << iMessage
             << std::endl;
    std::lock_guard<std::mutex> lock(log_mutex);
    std::cout << logEntry.str();
}
}
