#include <bits/stdc++.h>
#include <vector>

#define MAX 500 + 1
using namespace std;

const int dr[] = {0, 0, 1, -1};
const int dc[] = {1, -1, 0, 0};
int n, m;
string backyard[MAX];
int nsheeps, nwolfs;

struct Cell{
    int r;
    int c;
};

bool isValid(int r, int c) {
    return r >= 0 && c >= 0 && r < n && c < m;
}

void BFS(Cell s)
{
    queue<Cell> q;
    q.push(s);

    bool canEscape = false;
    int sheeps = (backyard[s.r][s.c] == 'k');
    int wolfs  = (backyard[s.r][s.c] == 'v');

    backyard[s.r][s.c] = '#';

    while(!q.empty())
    {
        auto u = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int r = u.r + dr[i];
            int c = u.c + dc[i];

            // verify if sheeps and wolfs is on the border or not
            if (!isValid(r, c)){
                canEscape = true;
                continue;
            }

            // calculate the number of wolf and sheep in zone
            if (backyard[r][c] != '#')
            {
                sheeps += (backyard[r][c] == 'k');
                wolfs  += (backyard[r][c] == 'v');
                backyard[r][c] = '#';
                q.push((Cell){r, c});
            }
        }    
    }

    if (canEscape)
    {
        nsheeps += sheeps;
        nwolfs  += wolfs;
    }
    else
    {
        sheeps > wolfs ? nsheeps += sheeps : nwolfs += wolfs;
    }
}


int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        cin >> backyard[i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (backyard[i][j] != '#')
            {
                BFS((Cell){i, j});
            }
        }
    }
    cout << nsheeps << " " << nwolfs;
    return 0;
}