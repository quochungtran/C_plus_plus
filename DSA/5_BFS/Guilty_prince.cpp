#include <bits/stdc++.h>
#define MAX 21
using namespace std;

const int dr[] = {0, 0 ,1 , -1};
const int dc[] = {1, -1, 0, 0};
int W, H;
int visited[MAX][MAX];
char maze[MAX][MAX];

struct Cell{
    int r;
    int c;
};

bool isValid(int r, int c)
{
    return r >=0 && c >= 0 && r < H && c < W;
}

int BFS(Cell s)
{
    queue<Cell> q;
    q.push(s);
    visited[s.r][s.c] = true;

    int count = 1;

    while(!q.empty())
    {
        auto u = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int r = u.r + dr[i];
            int c = u.c + dc[i];

            if (isValid(r, c) && maze[r][c] == '.' && !visited[r][c])
            {
                visited[r][c] = true;
                q.push((Cell){r, c});
                count++;
            }
        }
    }

    return count;
}


int main()
{
    Cell s;
    int Q;
    cin >> Q;

    for (int k=1; k <= Q; k++)
    {
        cin >> W >> H;

        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                cin >> maze[i][j];

                if (maze[i][j] == '@')
                {
                    s.r = i;
                    s.c = j;
                }

                visited[i][j] = false;
            }
        }
        cout << "Case " << k << ": " << BFS(s) << endl;
    }
    return 0;
}