#include <iostream>
#include <vector>

using namespace std;

#define N 9

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            cout << grid[row][col] << " ";
        cout << endl;
    }
    cout << endl;
}

// Function to check if it is safe to place a number in a cell
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if 'num' is not in the current row
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num)
            return false;

    // Check if 'num' is not in the current column
    for (int x = 0; x < N; x++)
        if (grid[x][col] == num)
            return false;

    // Check if 'num' is not in the current 3x3 box
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Function to solve the Sudoku using backtracking
bool solveSudoku(int grid[N][N], int row, int col) {
    // If we have reached the 9th row and 9th column, we are done
    if (row == N - 1 && col == N)
        return true;

    // If column value becomes 9, we move to the next row and column starts from 0
    if (col == N) {
        row++;
        col = 0;
    }

    // If the current position is already filled, we move to the next column
    if (grid[row][col] != 0)
        return solveSudoku(grid, row, col + 1);

    for (int num = 1; num <= 9; num++) {
        // Check if it is safe to place the number
        if (isSafe(grid, row, col, num)) {
            // Place the number
            grid[row][col] = num;

            // Check if we can solve the Sudoku with this number
            if (solveSudoku(grid, row, col + 1))
                return true;
        }

        // If placing the number doesn't lead to a solution, remove it
        grid[row][col] = 0;
    }
    return false;
}

int main() {
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Unsolved Sudoku grid:\n";
    printGrid(grid);

    if (solveSudoku(grid, 0, 0)) {
        cout << "Solved Sudoku grid:\n";
        printGrid(grid);
    } else {
        cout << "No solution exists";
    }

    return 0;
}
