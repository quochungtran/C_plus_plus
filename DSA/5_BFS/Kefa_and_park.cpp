#include <bits/stdc++.h>
#define MAX 100000 + 5
using namespace std;

int n, m;
int a[MAX], cat[MAX];
bool visited[MAX];
vector<int> graph[MAX];

int BFS(int s) {
    int nrestaurants = 0;
    queue<int> q;
    visited[s] = true;
    q.push(s);

    cat[s] = (a[s] == 1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int &v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;

                if (a[v] == 1) {
                    cat[v] = cat[u] + 1;
                }

                if (cat[v] <= m) {
                    if (graph[v].size() == 1) {
                        nrestaurants++;
                    }
                    else {
                        q.push(v);
                    }
                }
            }
        }
    }

    return nrestaurants;
}

int main() {
    int u, v;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cout << BFS(1);
    return 0;
}