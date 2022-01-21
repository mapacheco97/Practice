#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>

using namespace std;

#define empty 0
#define N 9

bool isGridSafe(int grid[N][N], int row, int col, int num);
bool isEmptyLocation(int grid[N][N], int& row, int& col);
bool SolveSudoku(int grid[N][N]);

/*
	assign values to all the non assigned values for Sudoku solution
*/
bool SolveSudoku(int grid[N][N]) {
	int row, col;
	if (!isEmptyLocation(grid, row, col)) {
		return true;
	}

	for(int num = 1; num <= 9; num++){
		if (isGridSafe(grid, row, col, num)) {
			grid[row][col] = num;
			if (SolveSudoku(grid)) {
				return true;
			}
			grid[row][col] = empty;
		}
	}
	return false;
}

/*
	check for entries that don't have a value
*/

bool isEmptyLocation(int grid[N][N], int &row, int &col) {
	for (row = 0; row < N; row++) {
		for (col = 0; col < N; col++) {
			if (grid[row][col] == empty)
				return true;
		}
	}
	return false;
}

bool UsedInRow(int grid[N][N], int prow, int number) {
	for (int col = 0; col < N; col++) {
		if (grid[prow][col] == number) {
			return true;
		}
	}
	return false;
}

/*
	returns true if the number num matches any number in the column
*/

bool UsedInCol(int grid[N][N], int pcol, int number) {
	for (int row = 0; row < N; row++) {
		if (grid[row][pcol] == number)
			return true;
	}
	return false;
}

//check if the entry has already been used

bool UsedInBox(int grid[N][N], int boxBeginRow, int boxBeginCol, int number) {
	bool used = false;

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (grid[row + boxBeginRow][col + boxBeginCol] == number)
				used = true;
		}
	}
	return used;
}

//checks if number can be assigned to a given prow, pcol location
bool isGridSafe(int grid[N][N], int prow, int pcol, int number) {
	return !UsedInRow(grid, prow, number) && !UsedInCol(grid, pcol, number) &&
		!UsedInBox(grid, prow - prow % 3, pcol - pcol % 3, number);
}

//print result
void printGrid(int finalGrid[N][N]) {
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			cout << finalGrid[row][col] << " ";
		}
		cout << endl;
	}
}

int main() {
	int grid[N][N] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
					  {0, 0, 0, 0, 0, 3, 0, 8, 5},
					  {0, 0, 1, 0, 2, 0, 0, 0, 0},
					  {0, 0, 0, 5, 0, 7, 0, 0, 0},
					  {0, 0, 4, 0, 0, 0, 1, 0, 0},
					  {0, 9, 0, 0, 0, 0, 0, 0, 0},
					  {5, 0, 0, 0, 0, 0, 0, 7, 3},
					  {0, 0, 2, 0, 1, 0, 0, 0, 0},
					  {0, 0, 0, 0, 4, 0, 0, 0, 9} };

	if (SolveSudoku(grid) == true)
		printGrid(grid);
	else
		cout << "No Solution Found" << endl;

	return 0;
}