/*
62. Unique Paths

There is a robot on an m x n grid. The robot is initially located at the top-left corner (i.e., grid[0][0]). 
The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move either down or right at any point in time.

Given the two integers m and n, return the number of possible unique paths that the robot can take to reach the bottom-right corner.
The test cases are generated so that the answer will be less than or equal to 2 * 109.

*/

void fill(int **arr, int m, int n)
{
    
    for (size_t i = 0; i < n; i++)
    {
        arr[0][i] = 1;    
    }

    for (size_t i = 0; i < m; i++)
    {
        arr[i][0] = 1;
    }  
}

int **construct_2D_arr(int m, int n)
{
    int **arr = (int **) malloc(m * sizeof(int *));
    for (size_t i = 0; i < m; i++)
        arr[i] = (int *) malloc(n * sizeof(int));

    return arr;   
}

void destruct_2d_arr(int **arr, int m, int n)
{
    for (size_t i = 0; i < m; i++)
        free(arr[i]);

    free(arr);
}

int uniquePaths(int m, int n) 
{
    int **arr = construct_2D_arr(m, n);
    
    fill(arr, m, n);

    for (size_t i = 1; i < m; i++)
    {
        for (size_t j = 1; j < n; j++)
        {
            arr[i][j] = arr[i - 1][j] + arr[i][j - 1];
        }
    }
    
    int res = arr[m - 1][n - 1];

    destruct_2d_arr(arr, m, n);

    return res;
}