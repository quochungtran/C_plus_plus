#include <iostream>

using namespace std;

#define N 4


void printSolution(vector<int>& board)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        { 
            cout << " " << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool check(vector<int>& board, int row, int col)
{
    // check vertical
    for (int i = 0; i < row; i++)
    {
        if (board[i][col]) return false;
    }

    // check main diagonal
    for (int i = row, j = col; j < N && i >= 0; i--; j++)
    {
        if (board[i][j]) return false;
    }

    // check the second diagonal
    for (int i = col, j = row; i < N && j >= 0; j--; i++)
    {
        if (board[i][j]) return false;
    }

    return true;
}

bool NQueen(vector<int>& board, int row)
{
    if (row == N)
    {
        printSolution(board);
        return true;
    }

    for (int j = 0; j < N; j++)
    {
        // check if the queen can be placed on chessboard
        if (check(board, row, j) == true)
        {
            // place this queenm in board[row][j]
            board[row][j] = 1;
            NQueen(board, row+1);
            // Backtracking
            board[row][j] = 0;
        }
    }

    return false;
}

int main()
{
    vector<int> board(N, 0);
    NQueen(board, 0);
    return 0;
}