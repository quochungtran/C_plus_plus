#include <iostream>
#include <bitset>
using namespace std;

namespace bitmanipulation {

unsigned int bitReversal(unsigned int n)
{
    int s = 8;
    unsigned int rev = 0;

    while(n != 0)
    {
        // shift left
        rev <<= 1;

        rev ^= (n & 1);
        
        // shift right
        n >>= 1;

        s--;
    }

    if (s > 0)
        rev <<= s;

    return rev;
}

}