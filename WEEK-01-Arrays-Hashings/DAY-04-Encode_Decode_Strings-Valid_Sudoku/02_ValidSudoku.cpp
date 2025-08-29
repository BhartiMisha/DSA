/*
Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
Note:

A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.
*/



/*
APPROACHES:

1. Brute-force:
    Check if the frequency of each number [0-9] is less than one in a row
    Check if the frequency of each number [0-9] is less than one in a column
    
    Each sub-box starts at indices (0,0), (0,3), (0,6), (3,0), (3,3), (3,6), (6,0), (6,3), (6,6)
    So, for i in {0,3,6} and j in {0,3,6}, you can iterate over the 3×3 block.
    Track the frequency of element in each block

    if freq for any element in any check is greater than 0 then its not a sudoku, else a sudoku

    Time Complexity: O(n^2) = O(81) = O(1)
    Space Complexity: O(n) = O(9) = O(1)




2. Hashed maps
    Same approach as the first one, it's just that we'll be doing everything in the same loop
    Create a map of int and map [unordered_map<int, unordered_map<char, int>>] for rows and cols
    The above map is to store freq of each element of each row and col
    Create another map [map<pair<int, int>, unordered_map<char, int>>] to store frequency of elements of a sub-box (3x3)
    The pair will contain index of each sub box as we divide the big box to 3x3 box of small boxes
    So the index of small boxes will be [0,0], [0,1], [0,2], [1,0]....[2,0], [2,1], [2,2]
    Now iterate over each elements of the matrix (nested loop)
    If the current element is '.' skip
    Increase frequency of each row element and column element
    check if freq of that element for that row or column is greater than 1 then return false
    Increase frequency of an item in the small box (pair) 
    If this freq is greater than 1, return false
    In the end, return true

    Time Complexity: O(n^2)
    Space Complexity: O(n^2)
*/



#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

class Solution {
    public:
        bool isValidSudoku(vector<vector<char>>& board) {
            // APPROACH 1: Brute-force
            // calculate frequency of each row and return false if the freq arr has a freq greater than 1
            // for(int i = 0; i < 9; i++){
            //     vector<int> freq(9, 0);
            //     for(int j = 0; j < 9;  j++){
            //         if(board[i][j] == '.')
            //             continue;
            //         int num = board[i][j] - '1';
            //         if(num < 0 || num > 8) return false;  // safety check
            //         freq[num]++;
            //         if(freq[num] > 1) return false;
            //     }
            // }
    
            // // calculate frequency of each column and return false if the freq arr has a freq greater than 1
            // for(int i = 0; i < 9; i++){
            //     vector<int> freq(9, 0);
            //     for(int j = 0; j < 9;  j++){
            //         if(board[j][i] == '.')
            //             continue;
            //         int num = board[j][i] - '1';
            //         if(num < 0 || num > 8) return false;  // safety check
            //         freq[num]++;
            //         if(freq[num] > 1) return false;
            //     }
            // }
    
            // // check each if 3x3 sub-board
            // for(int i = 0; i < 9; i+=3)
            // {
            //     for( int j = 0; j < 9; j+=3)
            //     {
            //         vector<int> freq(9, 0);
            //         for(int m = 0; m < 3; m++)
            //         {
            //             for(int n = 0; n < 3; n++)
            //             {
            //                 if(board[i+m][j+n] == '.')
            //                     continue;
            //                 int num = board[i+m][j+n] - '1';
            //                 if(num < 0 || num > 8) return false;  // safety check
            //                 freq[num]++;
            //                 if(freq[num] > 1) return false;
            //             }
            //         }
            //     }
            // }
    
            // // return true
            // return true;




            // APPROACH 2: Hashed map
            int n = 9;
            unordered_map<int, unordered_map<char, int>> rows, cols;
            map<pair<int, int>, unordered_map<int, int>> m;
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++) {
                    if(board[i][j] == '.')
                        continue;

                    // row check
                    rows[i][board[i][j]]++;
                    if(rows[i][board[i][j]] > 1)
                        return false;

                    // cols check
                    cols[j][board[i][j]]++;
                    if(cols[j][board[i][j]] > 1)
                        return false;

                    // Sub-box check
                    int row = i/3;
                    int col = j/3;
                    m[{row, col}][board[i][j]]++;
                    if(m[{row, col}][board[i][j]] > 1)
                        return false;
                }
            }
            return true;
        }
    };

int main() {
    // Example Sudoku board (partially filled, valid)
    vector<vector<char>> board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };

    Solution sol;
    bool result = sol.isValidSudoku(board);

    if(result) {
        cout << "The Sudoku board is valid." << endl;
    } else {
        cout << "The Sudoku board is NOT valid." << endl;
    }

    return 0;
}