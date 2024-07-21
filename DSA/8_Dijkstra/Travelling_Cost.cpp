#include <vector>
#include <stack>
#include <bits/stdc++.h>
#define MAX 505

using namespace std;
int N;
int A, B, W;
int U;
int Q, V;
const int INF = 1e9 + 7;
vector<vector<pair<int, int>>> graph;
vector<int> dist(MAX, INF);

struct option{
    bool operator() (const pair<int,  int>& a, const pair<int, int>& b)
    {
        return a.second > b.second;
    }
};

void Disjktra(int s)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, option> pq;
    pq.push(make_pair(s, 0));
    dist[s] = 0;

    while(!pq.empty())
    {
        auto [u, w] = pq.top();
        pq.pop();

        for (auto neighbor : graph[u])
        {
            if (w + neighbor.second < dist[neighbor.first])
            {
                dist[neighbor.first] = w + neighbor.second;
                pq.push(pair<int, int>(neighbor.first, dist[neighbor.first]));
            }
        }
    }
}

int main() {
    cin >> N;
    graph = vector<vector<pair<int, int>>>(MAX, vector<pair<int, int>>());
    for (int i = 0; i < N; i++)
    {
        cin >> A >> B >> W;
        graph[A].push_back(make_pair(B, W));
        graph[B].push_back(make_pair(A, W));
    }

    cin >> U;
    cin >> Q;

    Disjktra(U);

    for (int i = 0; i < Q; i++)
    {
        cin >> V;
        if (dist[V] != INF)
        {
            cout << dist[V] << endl;
        }
        else
        {
            cout << "NO PATH" << endl;
        }
    } 

    return 0;
}
