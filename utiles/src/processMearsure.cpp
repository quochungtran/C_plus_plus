#include <iostream>
#include <chrono>
#include <functional>

#include "UP_Time.h"

namespace utiles
{

template <typename timeType>
class Timer {
public:
    template <typename Func, typename... Args>
    static auto measure(Func&& func, Args&&... args) {
        using namespace std::chrono;
        auto start = high_resolution_clock::now();        
        auto result = std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
        auto end = high_resolution_clock::now();
                
        long long elapsed = 0;
        elapsed = std::chrono::duration_cast<timeType>(end-start).count();

        std::cout << "Execution time: " << elapsed << "\n";
        return result;
    }
};

} // namespace utiles


int main()
{
    using namespace utiles;
    auto sumLambda = [](int n){
        long long sum = 0;
        for (int i = 0; i < n; i++){
            sum += i;
        }
        return sum;
    };
    Timer<std::chrono::microseconds>::measure(sumLambda, 10000000000);
    return 0;
}