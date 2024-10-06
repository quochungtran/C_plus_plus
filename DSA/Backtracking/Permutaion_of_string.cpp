#include <string>
#include <iostream>

using namespace std;

void permutaion(string s, int l, int r)
{
    if (l == r)
    {
        cout << s << " ";
        return;
    }

    for (int i = l; i < r; i++)
    {
        swap(s[i], s[l]);
        permutaion(s, l+1, r);
        swap(s[i], s[l]);
    }
}

int main()
{
    string str;
    cin >> str;

    permutaion(str, 0, str.size());

    return 0;
}