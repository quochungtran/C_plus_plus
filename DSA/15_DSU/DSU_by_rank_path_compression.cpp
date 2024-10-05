#include <iostream>
using namespace std;

#define MAX 20

int parent[MAX + 5];
int ranks[MAX + 5];


void makeSet()
{
    for (int i = 1; i <= MAX; i++)
    {
        parent[i] = i;
        ranks[i] = 0;
    }
}

// O(logN)
int findSet(int u)
{
    if (parent[u] != u)
    {
        parent[u] = findSet(parent[u]);
    }

    return parent[u];
}


void unionSet(int u, int v)
{
    int up = findSet(u);
    int vp = findSet(v);

    if (up == vp)
    {
        return ;
    }

    if (ranks[up] > ranks[vp])
    {
        parent[vp] = up;
    }
    else if (ranks[up] < ranks[vp])
    {
        parent[up] = vp;
    }
    else
    {
        parent[up] = vp;
        ranks[vp]++;
    }
}

int main()
{
    int Q, u, v, q;
    cin >> Q;
    makeSet();

    for (int i = 0; i < Q; i++)
    {
        cin >> u >> v >> q;
        if (q == 1)
        {
            unionSet(u, v);
        }
        if (q == 2)
        {
            int parentU = findSet(u);
            int parentV = findSet(v);

            if (parentU == parentV)
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
        }
    }

    return 0;
}