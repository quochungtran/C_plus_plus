#include <iostream>
using namespace std;

#define MAX 20

int parent[MAX + 5];

// Complexity O(N) for 3 methods, where N is the number of elements

/**
 * Create a set for each inital elements
 *
 */
void makeSet()
{
    for (int i = 1; i <= MAX; i++)
    {
        parent[i] = i;
    }
}

/**
 * Find the element which is the presented of the set containing u
 */
int findSet(int u)
{
    while(u != parent[u])
    {
        u = parent[u];
    }

    return u;
}


/**
 * Union two set, one set containing u and one set containing v
 * if u and v including in one set => this doesn't work
 */
void unionSet(int u, int v)
{
    int up = findSet(u);
    int vp = findSet(v);

    parent[up] = vp;
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
                cout << "NO" << end;
            }
        }

        return 0;
    }
}