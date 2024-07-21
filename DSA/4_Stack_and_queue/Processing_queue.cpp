#include <iostream>
#include <queue>
using namespace std;

int main() {
    int n, b;
    long long t, d, processing = 0;
    queue<long long> q;
    
    cin >> n >> b;

    for (int i = 0; i < n; i++) {
        cin >> t >> d;

        while (!q.empty() && q.front() <= t) {
            q.pop();
        }

        if (q.size() <= b) {
            processing = max(processing, t) + d;
            cout << processing << " ";
            q.push(processing);
        }
        else {
            cout << -1 << " ";
        }
    }
    return 0;
}