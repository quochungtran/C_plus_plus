#include <iostream>
#include <string>
using namespace std;

int main() {
    int n, k;
    int cnt[101] = {0};
    string s, password;
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> s;
        cnt[s.size()]++;
    }

    cin >> password;

    int best_time = 0, worst_time = 0;

    for (int i = 0; i < password.size(); i++) {
        best_time += cnt[i];
    }

    worst_time = best_time + cnt[password.size()] - 1;
    
    best_time += (best_time / k) * 5;
    worst_time += (worst_time / k) * 5;

    cout << best_time + 1 << " " << worst_time + 1;
    return 0;
}