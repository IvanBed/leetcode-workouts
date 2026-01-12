/*
		494. Target Sum

You are given an integer array nums and an integer target.

You want to build an expression out of nums by adding one of the symbols '+' and '-' before each integer in nums and then concatenate all the integers.

For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and concatenate them to build the expression "+2-1".
Return the number of different expressions that you can build, which evaluates to target.
*/
// Backtracking solution	
class Solution1 {
private: 
    void findTargetSums(vector<int> const & nums, int target, int64_t cur_val, size_t index, int64_t & cnt)
    {
        if (index => nums.size())
        {
            cnt = cur_val == target ? cur_val : cnt;
        }
        findTargetSums(nums, target, cur_val + nums[index], index + 1, cnt);
		findTargetSums(nums, target, cur_val - nums[index], index + 1, cnt);
    }
	
public:    
    int findTargetSumWays(vector<int>& nums, int target) 
	{
        int64_t res = 0;
		findTargetSums(nums, target, 0, 0, res);
		return res;
    }
};

class Solution2 {
private: 
    void insert(map<int64_t, size_t> & map, int64_t val)
    {
        if (auto search = map.find(map[val]); search == map.end())
            map[val] = 1;
        else
            map[val]++;
    } 
	
public:    
    int findTargetSumWays(vector<int>& nums, int target) 
	{
        map<int64_t, size_t> dp_map;
        dp_map[nums[0]] = 1;
        dp_map[-nums[0]] = 1;
        for (size_t i = 1; i < nums.size(); i++)
        {
            map<int64_t, size_t> cur_dp_map;
            for (auto const& [key, val] : dp_map)
            {
                insert(cur_dp_map, key + nums[i]);
                insert(cur_dp_map, key - nums[i]);
            }
            dp_map = cur_dp_map;

        }
        if (auto search = dp_map.find(target); search == dp_map.end())
            return false;
        else
            return true;    
    }
};
