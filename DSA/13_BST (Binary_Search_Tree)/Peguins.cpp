#include <iostream>
#include <iomanip>
#include <cmath>
#include <map>
#include <set>
#include <bits/stdc++.h> 


// Complexity : O(NlogN)

using namespace std;

int main()
{
    int n;
    map<string, int> mp;
    string s;
    cin >> n;

    cin.ignore();

    for (int i = 0; i < n; i++)
    {
        getline(cin, s);
        mp[s]++;
    }

    string res;
    int maxx = -1;

    for (auto e : mp)
    {
        if (e.second > maxx)
        {
            maxx = e.second;
            res = e.first;
        }
    }

    cout << res;
    return 0;
}