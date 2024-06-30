#include <bits/stdc++.h>
#define MAX 21
using namespace std;

const int dr[] = {0, 0, 1, -1};
const int dc[] = {1, -1, 0, 0};
int n, m;
bool visited[MAX][MAX];
string maze[MAX];

struct Cell {
    int r, c;
};

bool isValid(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < m; 
}

bool BFS(Cell s, Cell f) {
    queue<Cell> q;
    visited[s.r][s.c] = true;
    q.push(s);

    while (!q.empty()) {
        Cell u = q.front();
        q.pop();
 
        if (u.r == f.r && u.c == f.c) {
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int r = u.r + dr[i];
            int c = u.c + dc[i];

            if (isValid(r, c) && maze[r][c] == '.' && !visited[r][c]) {
                visited[r][c] = true;
                q.push((Cell) {r, c});
            }
        }
    }
    
    return false;
}

int main() {
    int Q;
    cin >> Q;

    while (Q--) {
        cin >> n >> m;

        for (int i = 0; i < n; i++) {
            cin >> maze[i];
        }

        vector<Cell> entrance;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                visited[i][j] = false;
                if (maze[i][j] == '.' && (i == 0 || j == 0 || i == n - 1 || j == m - 1)) {
                    entrance.push_back((Cell) {i, j});
                }
            }
        }

        if (entrance.size() != 2) {
            cout << "invalid" << endl;
        }
        else {
            Cell s = entrance[0];
            Cell f = entrance[1];
            cout << (BFS(s, f) ? "valid" : "invalid") << endl;
        }
    }
    return 0;
}