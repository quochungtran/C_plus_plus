#pragma once
#include <thread>
#include <stdexcept>


class joining_thread {

private:
    std::thread t;

public:
    joining_thread() noexcept=default;
    template<template Callable, typename ...Args>
    explicit joining_thread(Callable&& func, Args&& ... args){
        t(std::forward<Callable>(func), std::forward(args));
    }
    
    joining_thread(std::thread other_t) {
        t(std::move(other_t));
    }

    joining_thread(joining_thread&& other){
        t(std::move(other.t));
    }

    joining_thread& operator=(joining_thread&& other) {
        if (joinable()){
            join();
        }

        t = std::move(other.t);
        return *this;
    }

    joining_thread& operator=(joining_thread other) {
        if (joinable()){
            join();
        }

        t = std::move(other.t);
        return *this;
    }

    joining_thread& operator=(std::thread other_t){
        if (joinable()){
            join();
        }
        
        t = std::move(other_t);
        return *this;
    }

    bool joinable(){
        return t.joinable();
    }

    void join(){
        t.join();
    }

    void detach(){
        t.detach();
    }

    void swap(joining_thread& other) {
        t.swap(other.t);
    }
};