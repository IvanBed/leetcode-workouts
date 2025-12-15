/*
	64. Minimum Path Sum

Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.
Note: You can only move either down or right at any point in time.

*/

void refill_matrix(int **grid, int gridSize, int gridColSize)
{
    for (size_t j = 1; j < gridColSize; j++) 
        grid[0][j] = grid[0][j - 1] + grid[0][j];

    for (int i = 1; i < gridSize; i++) 
        grid[i][0] = grid[i - 1][0] + grid[i][0];
}

int minPathSum(int **grid, int gridSize, int *gridColSize) 
{
    size_t last_row = gridSize - 1;
    size_t last_column = *gridColSize - 1;

    refill_matrix(grid, gridSize, *gridColSize);
    for (size_t i = 1; i < gridSize; i++) {
        for (size_t j = 1; j < *gridColSize; j++) 
            grid[i][j] = grid[i][j] + fmin(grid[i - 1][j], grid[i][j - 1]);
    }
    return grid[last_row][last_column];
}