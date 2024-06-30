#include <bits/stdc++.h>
#define MAX 1000 + 5
using namespace std;

int V, E;
bool visited[MAX];
int dist[MAX];
vector<int> graph[MAX];

void BFS(int s) {
    queue<int> q;
    visited[s] = true;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int &v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    int Q, u, v, s;
    cin >> Q;

    while (Q--) {
        cin >> V >> E;

        for (int i = 0; i < MAX; i++) {
            graph[i].clear();
            visited[i] = false;
            dist[i] = 0;
        }
        
        for (int i = 0; i < E; i++) {
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        cin >> s;
        BFS(s);

        for (int i = 1; i <= V; i++) {
            if (i == s) {
                continue;
            }

            cout << (visited[i] ? dist[i] * 6 : -1) << " ";
        }

        cout << endl;
    }
    return 0;
}