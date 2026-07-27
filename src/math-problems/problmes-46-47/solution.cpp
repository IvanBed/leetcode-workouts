/*
Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.

*/

class Solution {
public:
    
    void generate_next_perms(std::set<vector<int>> &all_permutations, std::vector<vector<int>> &storage, vector<int> cur_permutation)
    {
        for (size_t i = cur_permutation.size() - 1; i > 0; i--)
        {
            std::swap(cur_permutation[i], cur_permutation[i - 1]);
            
            if (!all_permutations.contains(cur_permutation))
            {
                storage.push_back(cur_permutation);
            }
        }
    }

    vector<vector<int>> permute(vector<int>& nums) 
    {
        std::set<vector<int>> all_permutations;
        std::vector<vector<int>> temp_storage;
        temp_storage.push_back(nums);
        
        while (!temp_storage.empty())
        {
           vector<int> cur_permutation = temp_storage.back();
           temp_storage.pop_back();
           all_permutations.insert(cur_permutation);
           generate_next_perms(all_permutations, temp_storage, cur_permutation);
        }

        std::copy(all_permutations.begin(), all_permutations.end(), std::back_inserter(temp_storage));
        return temp_storage;
    }
};

/* Another approach to solve the 46 problem*/

class Solution {
public:
    
    void nextPermutation(vector<int>& nums) 
    {
        size_t fast = nums.size() - 1;
        size_t slow = nums.size() - 1;

        while (fast > 0 && slow > 0)
        {
            if (nums[slow] > nums[fast - 1])
            {
                std::swap(nums[slow], nums[fast - 1]);
                reverse(nums.begin() + fast, nums.end());
                return;
            }
            if (nums[fast] > nums[fast - 1])
            {
                slow--;
            }
            else
            {
                fast--;
            }
        }
        reverse(nums.begin(), nums.end());
    }


    vector<vector<int>> permute(vector<int>& nums) 
    {
        vector<vector<int>> permutations;
        vector<int> current_perm = nums;
       
        do 
        {
            nextPermutation(current_perm);
            permutations.push_back(current_perm);
        } while (current_perm != nums);
        
        return permutations;
    }
};