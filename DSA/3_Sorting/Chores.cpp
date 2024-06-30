/**
 * codeforce : Chores
 * https://codeforces.com/problemset/problem/169/A
 */


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
    int n, a, b; 
    cin >> n >> a >> b;

    vector<int> h(n);
    for (int i = 0; i < n; i++)
    {
        cin >> h[i];
    }

    sort(h.begin(), h.end());
    cout << h[b] - h[b-1];
    return 0;
}
