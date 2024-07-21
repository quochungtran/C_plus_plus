#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int MAX = 2005;

int ranked[MAX];

int main() {

    int n, rating;
    cin >> n;
    vector<int> ratings(n), sorted_ratings(n);

    for (int i = 0; i < n; i++) {
        cin >> rating;
        ratings[i] = sorted_ratings[i] = rating;
    }

    sort(sorted_ratings.begin(), sorted_ratings.end(), greater<int>());

    for (int i = 0; i < n; i++) {
        rating = sorted_ratings[i];

        if (!ranked[rating]) {
            ranked[rating] = i + 1;
        }
    }

    for (int& rating : ratings) {
        cout << ranked[rating] << " ";
    }

    return 0;
}