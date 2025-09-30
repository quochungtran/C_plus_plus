#include <iostream>
#include <chrono>
#include <functional>

#include "UP_Time.h"

namespace utiles
{
class Timer {
public:
    enum class Unit {Seconds, Milliseconds, Microseconds, Nanoseconds};
    template <typename Func, typename... Args>
    static auto measure(Func&& func, Args&&... args) {
        using namespace std::chrono;
        auto start = high_resolution_clock::now();        
        auto result = std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
        auto end = high_resolution_clock::now();
                
        long long elapsed = 0;

        switch (_unit) {
            case Unit::Seconds: {
                elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
                break;
            }
            case Unit::Milliseconds: {
                elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                break;
            }
            case Unit::Microseconds: {
                elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                break;
            }
            case Unit::Nanoseconds: {
                elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                break;
            }
        }

        std::cout << "Execution time: " << elapsed << "\n";
        return result;
    }
    static void setUnit(Unit u) { _unit = u; }

private:
    static Unit _unit;
};

Timer::Unit Timer::_unit = Timer::Unit::Milliseconds;

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
    Timer::setUnit(Timer::Unit::Milliseconds);
    Timer::measure(sumLambda, 10000000000);
    return 0;
}