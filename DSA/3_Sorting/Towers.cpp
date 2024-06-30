/**
 * codeforce: Sort the array
 * https://codeforces.com/problemset/problem/451/B
 */


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> mp(1000+1);
    int maxHeight = 0;

    for (int e : a)
    {
        mp[e]++;
        maxHeight = max(maxHeight, mp[e]);
    }

    int minTowers = 0;
    for (int i = 0; i < 1001; i++)
    {
        if (mp[i] != 0)
        {
            minTowers++;
        }
    }
    cout << maxHeight << " " << minTowers;

    return 0;
}

// sort approach

int main() {
    int n;
    cin >> n;
    vector<int> bars(n);

    for (int i = 0; i < n; i++) {
        cin >> bars[i];
    }

    sort(bars.begin(), bars.end());
    int n_towers = 1, max_height = 1, cur_height = 1;

    for (int i = 1; i < n; i++) {
        if (bars[i] == bars[i - 1]) {
            cur_height++;
            max_height = max(max_height, cur_height);
        }
        else {
            n_towers++;
            cur_height = 1;
        }
    }

    cout << max_height << " " << n_towers;
    return 0;
}