// all_of example
#include <iostream>     // std::cout
#include <algorithm>    // std::all_of
#include <array>        // std::array
#include <vector>

using namespace std;

bool isPerfectSquare(long long n)
{
    if (n <= 1)
    {
        return true;
    }
    long long left = 1;
    long long right = n;

    while(left <= right)
    {
        long long mid = left + (right - left)/2;
        long long square = mid * mid;

        if (square == n)
        {
            return true;
        }            
        else if (square < n)
        {
            left = mid+1;
        }
        else
        {
            right = mid-1;
        }
    }

    return false ;
}

int main () {
    std::array<int,8> foo = {3,5,7,11,13,17,19,23};

    if ( std::all_of(foo.begin(), foo.end(), [](int i){return i%2;}) )
    std::cout << "All the elements are odd numbers.\n";

    vector<int> arr = {1, 9, 81, 25};
    if (std::all_of(arr.begin(), arr.end(), [](int i){return isPerfectSquare(i);}))
    {
        std::cout << "All elements are perfect square";
    }

  return 0;
}
