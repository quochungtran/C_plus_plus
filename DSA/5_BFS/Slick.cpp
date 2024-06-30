#include <bits/stdc++.h>
#include <vector>

#define MAX 251
using namespace std;

const int dr[] = {0, 0, 1, -1};
const int dc[] = {1, -1, 0, 0};
int N, M;
int slick[MAX * MAX];
int table[MAX][MAX];

struct Cell{
    int r;
    int c;
};

bool isValid(int r, int c) {
    return r >= 0 && c >= 0 && r < N && c < M;
}

void BFS(Cell s) {
    queue<Cell> q;
    q.push(s);
    table[s.r][s.c] = 0;
    int count = 1;

    while (!q.empty()) {
        Cell u = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int r = u.r + dr[i];
            int c = u.c + dc[i];

            if (isValid(r, c) && table[r][c] == 1) {

                // table = 0, to be used to replace visited container
                table[r][c] = 0;
                q.push((Cell) {r, c});
                count++;
            }
        }
    }

    slick[count]++;
}

int main() {

    while(true)
    {
        cin >> N >> M;

        if (M == 0 && N == 0)
        {
            break;
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                cin >> table[i][j];
                slick[i * M + j + 1] = 0;
            }
        }

        int nslicks = 0;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (table[i][j] == 1)
                {
                    nslicks++;
                    BFS((Cell){i, j});
                }
            }
        }

        cout << nslicks << endl;

        for (int i = 1; i <= N * M; i++) {
            if (slick[i]) {
                cout << i << " " << slick[i] << endl;
            }
        }
    }
    return 0;
}