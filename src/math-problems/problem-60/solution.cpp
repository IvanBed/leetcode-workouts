/*

	The set [1, 2, 3, ..., n] contains a total of n! unique permutations.

	By listing and labeling all of the permutations in order, we get the following sequence for n = 3:

	"123"
	"132"
	"213"
	"231"
	"312"
	"321"
	Given n and k, return the kth permutation sequence.

*/

class Solution {
public:
    
    std::vector<int> makeVect(int n)
    {
        std::vector<int> res;
        
        for (size_t i = 1; i <= n; i++)
        {
            res.push_back(i);
        }
        return res;
    }

    std::string vectToString(vector<int>& nums)
    {
        std::string res = "";
        for (size_t i = 0; i < nums.size(); i++)
        {
            res += (char)(nums[i] + 48);  
        }
        return res;
    }

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
    
    std::vector<int> getPermutationInternal(vector<int>& nums, int k)
    {
        vector<int> current_perm = nums;
        for (size_t i = 0; i < k - 1; i++) 
        {
            nextPermutation(current_perm); 
        } 
        return current_perm; 
    }

    string getPermutation(int n, int k) 
    {
        std::vector<int> start_perm = makeVect(n);
        std::vector<int> target_perm = getPermutationInternal(start_perm, k);
        return vectToString(target_perm);
    }
};