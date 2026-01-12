/*
		494. Target Sum

You are given an integer array nums and an integer target.

You want to build an expression out of nums by adding one of the symbols '+' and '-' before each integer in nums and then concatenate all the integers.

For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and concatenate them to build the expression "+2-1".
Return the number of different expressions that you can build, which evaluates to target.

DP Ssolution
*/

class Solution {
private: 
    void insert(unordered_map<int64_t, size_t> & map, int64_t val, size_t prev_cnt)
    {
        map[val] =  map[val] + prev_cnt;
    } 
	
public:    
    int findTargetSumWays(vector<int>& nums, int target) 
	{
        unordered_map<int64_t, size_t> dp_map;
        if (nums[0] == 0)
        {
            dp_map[nums[0]] = 2;
        }
        else 
        {
            dp_map[nums[0]] = 1;
            dp_map[-nums[0]] = 1;
        }
        for (size_t i = 1; i < nums.size(); i++)
        {
            unordered_map<int64_t, size_t> cur_dp_map;
            for (auto const& [key, val] : dp_map)
            {
                insert(cur_dp_map, key + nums[i], val);
                insert(cur_dp_map, key - nums[i], val);
            }
            dp_map = cur_dp_map;
        }
        if (auto search = dp_map.find(target); search == dp_map.end())
            return 0;
        else
            return dp_map[target];    
    }
};