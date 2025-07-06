#include <iostream>

namespace log_system{

template<typename T>
void logType(T&& val){
    if constexpr (std::is_lvalue_reference<decltype(val)>::value){
        std::cout << "Lvalue" << "\n";
    }
    else{
        std::cout << "Rvalue" << "\n";
    }
}
}

using namespace log_system;

int main(){
    logType(4);
    int x = 5;
    logType(x);
}