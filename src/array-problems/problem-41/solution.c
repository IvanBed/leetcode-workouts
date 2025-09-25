/*	
	41. First Missing Positive

	Given an unsorted integer array nums. Return the smallest positive integer that is not present in nums.

	You must implement an algorithm that runs in O(n) time and uses O(1) auxiliary space.

	 

	Example:
	Input: nums = [1,2,0]
	Output: 3
	Explanation: The numbers in the range [1,2] are all in the array.

*/


int firstMissingPositive(int* nums, int nums_size) {

    int max = INT_MIN;
    for (size_t i = 0; i < nums_size; i++) {
        if (nums[i] <= 0) continue;
        if (nums[i] > max) max = nums[i];
        if (nums[i] - 1 < nums_size && i !=  nums[i] - 1 &&  nums[i] != nums[nums[i] - 1]){
            int temp = nums[nums[i] - 1];
            nums[nums[i] - 1] =  nums[i];
            nums[i] = temp;
            if(nums[i] > 0 && nums[i] < nums_size + 1 && nums[i] != i + 1)
                i--;   
        }
    }
    for (int i = 0; i < nums_size; i++) 
        if (nums[i] < 0  || i != nums[i] - 1)
            return i + 1;

    return max + 1;
}