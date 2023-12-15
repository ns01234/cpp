#include <iostream>
#include <map>
#include <vector>
using namespace std;

vector<char> validNums(vector<vector<char>>& board, int row, int col) {
        int r = row / 3 * 3;
        int c = col / 3 * 3;
        vector<char> v;
        map<char, bool> m;

        for (int i = 1; i <= 9; i++) {
            m[i + '0'] = true;
        }

        for (int i = 0; i < 9; i++) {
            m[board[row][i]] = false;
            m[board[i][col]] = false;
        }

        for (int i = r; i < r + 3; i++) {
            for (int j = c; j < c + 3; j++) {
                m[board[i][j]] = false;
            }
        }

        for (auto pair : m) {
            if (pair.second) {
                v.push_back(pair.first);
            }
        }

        return v;
    }

bool recursiveFiller(vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.') {
                vector<char> possibleNums = validNums(board, i, j);
                for (char num : possibleNums) {
                    board[i][j] = num;
                    if (recursiveFiller(board)) {
                        return true;
                    }
                    board[i][j] = '.';
                }
                return false;
            }
        }
    }
    return true;
}

void solveSudoku(vector<vector<char>>& board) {
    
    recursiveFiller(board);
}

int main ()
{

    vector<vector<char>> board = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };

    solveSudoku(board);
    cout << board[0][2];

    return 0;
}