#include <bits/stdc++.h>
#define MAX 100000 + 5
#define MOD 100000
using namespace std;

int N;
int dist[MAX];
int a[MAX];

int BFS(int s, int f) {
    memset(dist, -1, sizeof(dist));
    queue<int> q;
    q.push(s);
    dist[s] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < N; i++) {
            int v = (1LL * a[i] * u) % MOD;

            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);

				if (v == f) {
					return dist[v];
				}
            }
        }
    }

    return -1;
}

int main() {
    int s, f;
    cin >> s >> f >> N;

    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }

    cout << BFS(s, f);
    return 0;
}