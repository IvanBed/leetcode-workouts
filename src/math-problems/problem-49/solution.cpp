/*
									48. Rotate Image

You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. 
DO NOT allocate another 2D matrix and do the rotation.

*/

class Solution {
private:
    void rotate_vector(vector<int> & vect) 
    {
        size_t first = 0;
        size_t last = vect.size() - 1;
    
        while (first < last)
        {
            swap(vect[first++], vect[last--]);
        }
    }
    
    void rotate_matrix_horizontal(vector<vector<int>>& matrix)
    {
        for (auto & vect : matrix)
        {
            rotate_vector(vect);    
        }
    }

    void rotate_matrix_diagonal(vector<vector<int>>& matrix)
    {
        size_t last_el_index = matrix.size() - 1;

        for(size_t i = 0; i < matrix.size(); i++)
        {
            for (size_t j = 0; j <  matrix.size() - i; j++)
            {
                swap(matrix[i][j], matrix[last_el_index - j][last_el_index - i]);
            }
        }        
    }

public:
    void rotate(vector<vector<int>>& matrix) 
    {
        rotate_matrix_horizontal(matrix);
        rotate_matrix_diagonal(matrix);
    }

};