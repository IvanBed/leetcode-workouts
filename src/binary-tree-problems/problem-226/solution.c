/*
			Invert Binary Tree

Given the root of a binary tree, invert the tree, and return its roo

*/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 
 */
void swap(struct TreeNode *node)
{
    struct TreeNode* temp = node->left;
    node->left = node->right;
    node->right = temp;
}

void dfs(struct TreeNode *node)
{
    if (node == NULL)
        return;

    dfs(node->left);
    dfs(node->right);
    swap(node);

}

struct TreeNode* invertTree(struct TreeNode *root) 
{
    dfs(root);
    return root;
}