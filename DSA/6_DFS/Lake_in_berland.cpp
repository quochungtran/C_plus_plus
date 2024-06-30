#include <bits/stdc++.h>

#define MAX 51
using namespace std;

const int dr[] = {0, 0, -1, 1};
const int dc[] = {-1, 1, 0, 0};
int N, M, k;
bool visited[MAX][MAX];
string table[MAX];

struct Cell{
    int r;
    int c;
};

vector<vector<Cell>> lakes;

bool isValid(int r, int c)
{
    return r >= 0 && c >= 0 && r < N && c < M;
}

bool onBorder(int r, int c)
{
    return r == 0 || c == 0 || r == N - 1 || c == M - 1;
}

bool sortBySize(const vector<Cell>& a, const vector<Cell>& b)
{
    return a.size() < b.size();
}

void DFS(Cell scr)
{
    stack<Cell> s;
    s.push(scr);
    visited[scr.r][scr.c] = true;
    bool isOcean = false;
    vector<Cell> tmp;

    while(!s.empty())
    {
        auto u = s.top();
        tmp.push_back(u);
        s.pop();
        
        if (onBorder(u.r, u.c))
        {
            isOcean = true;
        }

        for (int i=0; i < 4; i++)
        {
            int r = u.r + dr[i];
            int c = u.c + dc[i];

            if (isValid(r, c) && table[r][c] == '.' && !visited[r][c])
            {
                s.push((Cell){r, c});
                visited[r][c] = true;
            }
        }
    }

    if (!isOcean)
    {
        lakes.push_back(tmp);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> N >> M >> k;

    for (int i = 0; i < N; i++)
    {
        cin >> table[i];
    }
    
    for (int i=0; i < N; i++)
    {
        for (int j=0; j < M; j++)
        {
            if (!visited[i][j] && table[i][j] == '.')
            {
                DFS((Cell){i, j});
            }
        }
    }

    sort(lakes.begin(), lakes.end(), sortBySize);

    int sum_cell = 0;

    for (int i = 0; i < lakes.size() - k; i++)
    {
        sum_cell += lakes[i].size();

        for (int j=0; j < lakes[i].size(); j++)
        {
            Cell u = lakes[i][j];
            table[u.r][u.c] = '*';
        }
    }

    cout << sum_cell << endl;

    for (int i=0; i < N; i++)
    {
        cout << table[i] << endl;
    }

    return 0;
}