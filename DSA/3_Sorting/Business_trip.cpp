/**
 * codeforce: Sort the array
 * https://codeforces.com/problemset/problem/451/B
 */


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int k;
    cin >> k;
    vector<int> a(12);
    for (int i = 0; i < 12; ++i) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());
    int sum = 0, count=0;

    for (int i = 11; i >= 0; i--)
    {
        if (sum >= k){
            break;
        }
        sum += a[i];
        count++;
    }
    if (count == 12 && sum < k)
    {
        cout << -1;
        return 0;
    }
    cout << count;
    return 0;
}
