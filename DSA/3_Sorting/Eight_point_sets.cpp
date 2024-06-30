/**
 * codeforce: Sort the array
 * https://codeforces.com/problemset/problem/451/B
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <utility>
using namespace std;

// Custom comparison function
bool customSort(const pair<int, int>& a, const pair<int, int>& b) {
    if (a.first != b.first) {
        return a.first < b.first;
    }
    return a.second < b.second;
}


int main() {
    vector<pair<int, int>> points(8);
    set<int> xs_unique;
    set<int> ys_unique;


    for (int i = 0; i < 8; i++) {
        int x, y;
        cin >> x >> y;
        points[i] = {x, y};
        xs_unique.insert(x);
        ys_unique.insert(y);
    }

    // Ensure there are exactly 3 unique elements in the set
    if (xs_unique.size() != 3 || ys_unique.size() != 3) {
        cout << "ugly";
        return 0;
    }

    // Convert the set to a vector for indexed access
    vector<int> xs(xs_unique.begin(), xs_unique.end());
    vector<int> ys(ys_unique.begin(), ys_unique.end());

    vector<pair<int, int>> eightPoints = {
        {xs[0], ys[0]}, {xs[0], ys[1]}, {xs[0], ys[2]},
        {xs[1], ys[0]}, {xs[1], ys[2]},
        {xs[2], ys[0]}, {xs[2], ys[1]}, {xs[2], ys[2]}
    };

    sort(points.begin(), points.end(), customSort);

    for (int i =0 ; i < 8; i++)
    {
       if (points[i] != eightPoints[i])        {
            cout << "ugly";
            return 0;
        }
    }

    cout << "respectable";
    return 0;
}
