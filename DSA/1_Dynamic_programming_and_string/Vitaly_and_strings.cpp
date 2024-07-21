#include <iostream>
#include <string>

using namespace std;

int main(){
    string s,t;
    cin >> s >> t;

    for (int i = s.size() - 1; i >= 0; i--)
    {
        if (s[i] == 'z')
        {
            s[i] = a;
        }
        else
        {
            s[i]++;
            break;
        }
    }

    cout << (s == t ? "No such string" : s);
}