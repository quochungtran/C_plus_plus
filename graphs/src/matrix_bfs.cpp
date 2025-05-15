

#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

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