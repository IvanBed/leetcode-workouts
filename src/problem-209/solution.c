/*
Given an array of positive integers nums and a positive integer target, 
return the minimal length of a subarray whose sum is greater than or equal to target. 
If there is no such subarray, return 0 instead.

Example 1:

Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.


*/

int minSubArrayLen(int target, int nums[], int size) 
{
    bool sum_flag = false;
    int min_len = size + 1;
    int cur_len = 0;
    int cur_sum = 0;
    int l = 0;
    int r = 0;

    while (r < size) 
    {
        cur_sum += nums[r];   
        while (cur_sum >= target) 
        {
            sum_flag = true;
            cur_len = r - l + 1;
            min_len = cur_len <= min_len? cur_len : min_len;
            cur_sum -= nums[l++];
        }           
        r++;
    }
    return sum_flag? min_len : 0;
}