#include <iostream>

using namespace std;

set<unsigned long long> S;
long long POW[10];
int test;
int n;
const int MAX_N = 10;
char a[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
int trace[10];
unsigned long long f[65];

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void DFS(int step, int x, int y)
{
    visited[x][y] = true;
    trace[step] = (x-1) * n + y - 1;

    if (step == 8){
        unsigned long long sum = 0LL;
        for (int i = 0; i <= 8; i++){
            sum |= f[trace[i]];
        }

        S.insert(sum);
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        int nxtx = i + dx[i];
        int nxty = i + dy[i];

        if (nxtx >= 1 && nxtx <= n && nxty >= 1 && nxty <= n && visited[nxtx][nxty] == false)
        {
            DFS(step+1, nxtx, nxty);
            visited[nxtx][nxty] = false;
        }
    }
}

int main()
{
    f[0] = 1LL;
    for (int i = 0; i <= 63; i++)
    {
        f[i] = f[i-1] << 1LL; // f[i] = 2^i
    }

    cin >> test;

    for (int i = 0; i <= n; i++)
    {
        cin >> n;

        for(int i = 0; i <= n; i++){
            cin >> a[i];
        }

        s.clear();

        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                for (int j = 1; j <= n; j++)
                {
                    visited[i][j] = false;
                }
            }
        }
    }

    return 0;
}