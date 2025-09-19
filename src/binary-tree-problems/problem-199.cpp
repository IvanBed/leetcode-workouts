/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };


	Given the root of a binary tree, imagine yourself standing on the right side of it, 
	return the values of the nodes you can see ordered from top to bottom.

	Example 1:

	Input: root = [1,2,3,null,5,null,4]

	Output: [1,3,4]
 
 */
 
class Solution {
public:
    
    void bfsMove(struct TreeNode *root, int cur_step, int &max_step, vector<int> &res) {

		if (!root)
			return;

		if (max_step == cur_step)
			res.push_back(root->val);


		cur_step++;
		
		if (cur_step > max_step) max_step = cur_step;

		bfsMove(root->right, cur_step, max_step, res);
		bfsMove(root->left, cur_step, max_step, res);
	}
    
    vector<int> rightSideView(TreeNode *root) {
		
        vector<int> res;
		
        if (root == nullptr) 
            return res;
		
        int max_step = 0;
        bfsMove(root, 0, max_step, res);
        
		return res;
    }
};