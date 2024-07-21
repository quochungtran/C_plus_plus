#include <iostream>
#include <string>
using namespace std;

int main(){
    string wheel;
    cin >> wheel;

    char pointer = 'a';
    int dist, count = 0;

    for (auto& c : wheel)
    {
        dist = abs(pointer - c);

        if (dist < 13)
        {
            count = count + dist;
        }
        else
        {
            count = count + (26 - dist);
        }

        pointer = c;
    }

    cout << count;
    return 0;
}
