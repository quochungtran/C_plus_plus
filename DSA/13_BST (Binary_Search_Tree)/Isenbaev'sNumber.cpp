// Type your code here, or load an example.
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>

using namespace std;

// adj list containing the adjent nodes of given index of original node
vector<int> adj[500];

// array to store distance from the source node and visited status for each node
int dis[1010];
int vis[1010];

void bfs(int s)
{
    queue<int> q;
    q.push(s);
    vis[s] = 1;

    while(!q.empty())
    {
        int f = q.front();
        q.pop();
        for (int i = 0; i < adj[f].size(); i++)
        {
            int e = adj[f][i];
            if (!vis[e])
            {
                vis[e] = 1;
                dis[e] = dis[f] + 1;
                q.push(e);
            }
        }
    }
}

int main()
{
    int n, p = 1;
    cin >> n;
  
  	// map bwt the name -> the index
    map<string, int> mp;
    map<string, int>::iterator it;

    for (int i = 0; i < n; i++)
    {
        string f, s, t;
        cin >> f >> s >> t;
        if (!mp[f])
        {
            mp[f] = p++;
        }

        if (!mp[s])
        {
            mp[s] = p++;
        }

        if (!mp[t])
        {
            mp[t] = p++;
        }
        adj[mp[f]].push_back(mp[s]);
        adj[mp[f]].push_back(mp[t]);
        adj[mp[s]].push_back(mp[f]);
        adj[mp[s]].push_back(mp[t]);
        adj[mp[t]].push_back(mp[f]);
        adj[mp[t]].push_back(mp[s]);
    }

		bfs(mp["Isenbaev"]);

    for (it = mp.begin(); it != mp.end(); it++)
    {
        if (it->second == 0)
            continue;

        if (!vis[it->second])
        {
            cout << it->first << " undefined" << endl;
        }
        else
        {
            cout << it->first << " " << dis[it->second] << endl;
        }
    }

    return 0;
}