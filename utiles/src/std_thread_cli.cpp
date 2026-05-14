#include <thread>
#include <string> 
#include <memory>
#include "logging.h"
#include <cassert>

void process_data(std::string msg) {
    // LOG(LogLevel::INFO, "running a thread: ", msg);
    LOG(LogLevel::DEBUG, "thread 1");
    utiles::Logger::log(LogLevel::INFO, msg);
}

void updatePtr(std::unique_ptr<int> p) {
    LOG(LogLevel::DEBUG, "thread 3");
    if (p)
        LOG(LogLevel::INFO, *p);
}

void updateCounter(int& counter) {
    LOG(LogLevel::DEBUG, "thread 2");
    counter++;
}

int main(){
    std::string s = "hello";
    std::thread t1(process_data, s);

    int counter = 0;
    std::thread t2(updateCounter, std::ref(counter));

    auto p = std::make_unique<int>(99);

    assert(p);

    std::thread t3(updatePtr, std::move(p));
    t1.join();
    t2.join();
    t3.join();
    LOG(LogLevel::INFO, counter);
    assert(!p);
}