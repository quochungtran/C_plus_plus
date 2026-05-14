#include <thread>
#include <string> 
#include <memory>
#include "logging.h"

void process_data(std::string msg) {
    // LOG(LogLevel::INFO, "running a thread: ", msg);
    utiles::Logger::log(LogLevel::INFO, msg);
}

int main(){
    std::string s = "hello";
    std::thread t1(process_data, s);

    t1.join();
}