#include <iostream>
#include <queue>
#include <vector>

#define MAX 100000

using namespace std;

int N;
long long A[MAX];

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    if (N <= 2) {
        for (int i = 0; i < N; i++) {
            cout << -1 << endl;
        }
        return 0;
    }

    long long pd = 1;
    priority_queue<long long, vector<long long>, greater<long long>> pq;

    for (int i = 0; i < N; i++) {
        if (i < 3) {
            pq.push(A[i]);
            pd *= A[i];
            if (i < 2) {
                cout << -1 << endl;
            } else {
                cout << pd << endl;
            }
        } else {
            if (A[i] > pq.top()) {
                pd /= pq.top();
                pq.pop();
                pq.push(A[i]);
                pd *= A[i];
            }
            cout << pd << endl;
        }
    }

    return 0;
}
