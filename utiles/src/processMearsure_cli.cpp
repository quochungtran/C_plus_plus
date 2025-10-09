#include "processMearsure.hpp"


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