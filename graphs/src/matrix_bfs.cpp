

#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;
#include <bits/stdc++.h>

namespace algorithm::graph{
struct Pos
{
    int x;
    int y;
    int distance;
    Pos(int x, int y, int distance=0) : x(x), y(y), distance(distance){}

    bool operator==(const Pos& iPos) const {return iPos.x == x && iPos.y == y;}
};

const vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; 

bool isReachToTarget(const Pos& curPos, const Pos& targetPos)
{
    return curPos == targetPos;
}

bool isInBound(const Pos& curPos, vector<vector<int>>& grid)
{
    int ROWS = grid.size(), COLS = grid[0].size();
    return curPos.x >= 0 && curPos.x <= ROWS-1 && curPos.y >= 0 && curPos.y <= COLS-1;
}

int bfs(std::vector<std::vector<int>>& grid)
{
    int ROWS = grid.size();
    int COLS = grid[0].size();

    vector<vector<int>> visit(4, vector<int>(4));

    queue<Pos> queue;    
    queue.push(Pos(0 ,0));

    visit[0][0] = 1;

    int length = 0;

    while (queue.size())
    {
        int queueLength = queue.size();
        for (int i = 0; i < queueLength; i++){
            auto curPos = queue.front();
            queue.pop();

            if (isReachToTarget(curPos, Pos(ROWS-1, COLS-1)))
            {
                return length;
            }

            for (auto& direction: directions)
            {
                auto newPos = Pos(curPos.x + direction[0], curPos.y + direction[1]);
                if (!isInBound(newPos, grid) || visit[newPos.x][newPos.y] == 1 || grid[newPos.x][newPos.y])
                {
                    continue;
                }

                queue.push(newPos);
                visit[newPos.x][newPos.y] = 1;
            }
        }
        length++;
    }
    return length;
}

int bfsShortestPath(vector<vector<int>>& grid, 
                    int k, 
                    pair<int, int> start,
                    pair<int, int> end){
    int rows = grid.size();
    int cols = grid[0].size();
    
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
    vector<vector<int>> dir {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    q.push(start);
    visited[start.first][start.second] = true;
    dist[start.first][start.second] = 0;
    
    while(!q.empty()){
        auto curr = q.front();
        q.pop();
        auto curr_x = curr.first;
        auto curr_y = curr.second;
        
        // always check the condition here
        if (curr == end) {
            return dist[curr_x][curr_y];
        }

        for (int i = 0; i < 4; i++){
            for (int step = 1; step <= k; step++){
                auto new_x = curr_x + step * dir[i][0];
                auto new_y = curr_y + step * dir[i][1];

                // change the direction when we face the ostacles, we can jump to the cell behind
                // the ostacle
                if (new_x < 0|| new_y < 0 || new_x >= rows || new_y >= cols || grid[new_x][new_y] == 1){
                    break;
                }
                
                // once we hit a visited cell in this direction, stop going further
                // since you will jump through the visited node => violate BFS exploration
                if (visited[new_x][new_y]){
                    break;
                }

                dist[new_x][new_y] = dist[curr_x][curr_y] + 1;
                // make sure we put in the visited at the end
                visited[new_x][new_y] = true;
                q.push({new_x, new_y});
            }
        }
    }
    
    return -1;
}

}