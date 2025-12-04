/*
                77. Combinations

Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].

You may return the answer in any order.

*/
#include <vector>
// Итеративный вариант генерации сочетаний n по k
void generate(vector<vector<int>> & res_arr, vector<int> & tuple, int n)
{
    size_t last_el_index = tuple.size() - 1;
	while (tuple[last_el_index] < n) 
    {
        res_arr.push_back(tuple);
        tuple[last_el_index]++;
    }
    res_arr.push_back(tuple);
}

bool check_and_reorder(vector<int> & tuple, vector<int> const & max_values)
{
    if (tuple[0] == max_values[0])
        return false;
    
    for(size_t i = 1; i < tuple.size(); i++)
    {
        if (tuple[i] == max_values[i])
        {
            tuple[i - 1]++;
            int j = i;
            while(j < tuple.size())
            {
                tuple[j] = tuple[j - 1] + 1;
                j++;
            }
            break;
        }
    }
    return true;
}

void fill_tuple(vector<int> & tuple, int k) 
{
    for (int i = 1; i <= k; i++)
        tuple.push_back(i);  
}    

void fill_max_values(vector<int> & max_values, int n, int k) 
{
    for (int i = 1; i <= k; i++)
        max_values.push_back(n - k + i);        
}

vector<vector<int>> combine(int n, int k)
{
    vector<vector<int>> res_arr;
    
    vector<int> tuple;
    vector<int> max_values; 
    fill_tuple(tuple, k);
    fill_max_values(max_values, n, k);
    bool state = true;
    
    while(state)
    {
        generate(res_arr, tuple, n);
        state = check_and_reorder(tuple, max_values);
    }  
    return res_arr;
}