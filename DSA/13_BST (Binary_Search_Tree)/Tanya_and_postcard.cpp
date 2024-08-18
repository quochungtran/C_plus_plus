#include <iostream>
#include <map>
#include <algorithm>
using namespace std;


// T*Log(K)
int main() {
    string message, newspaper;
    map<int, int> a, b;
    int n, m, yay = 0, whoops = 0;
    cin >> message >> newspaper;
    
  	// in ASCII table, 0 meaning the bull char
    for (int i = 0; message[i] != 0; i++) {
        int id = message[i] - 'A';
        if (message[i] > 'Z')
            id = message[i] - 'a' + 26;
        a[id]++;
    }
    for (int i = 0; newspaper[i] != 0; i++) {
        int id = newspaper[i] - 'A';
        if (newspaper[i] > 'Z')
            id = newspaper[i] - 'a' + 26;
        b[id]++;
    }
    
    for (int i = 0; i < 52; i++) {
        int tmp = min(a[i], b[i]);
        yay += tmp;
        a[i] -= tmp; b[i] -= tmp;
    }
    for (int i = 0; i < 26; i++) {
        whoops += min(a[i], b[i+26]) + min(a[i+26], b[i]);
    }
    cout << yay << " " << whoops;
    return 0;
}