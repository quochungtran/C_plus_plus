#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> bars(n);

    for (int i = 0; i < n; i++) {
        cin >> bars[i];
    }

    int curr_height = 1, max_height = 1, n_towers = 1;
    sort(bars.begin(), bars.end());

    for (int i = 1; i < bars.size(); i++)
    {
        if (bars[i-1] == bars[i])
        {
            curr_height++;
            max_height = max(max_height, curr_height);
        }
        else
        {
            n_towers++;
            cur_height = 1;
        }
    }

    cout << max_height << " " << n_towers;
    return 0;
}