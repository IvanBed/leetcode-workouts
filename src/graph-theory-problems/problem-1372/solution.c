/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
 /*
							1372. Longest ZigZag Path in a Binary Tree

You are given the root of a binary tree.

A ZigZag path for a binary tree is defined as follow:

Choose any node in the binary tree and a direction (right or left).
If the current direction is right, move to the right child of the current node; otherwise, move to the left child.
Change the direction from right to left or from left to right.
Repeat the second and third steps until you can't move in the tree.
Zigzag length is defined as the number of nodes visited - 1. (A single node has a length of 0).

Return the longest ZigZag path contained in that tree.
 
 
 */
#define LEFT 0
#define RIGHT 1
#define ROOT 2

void zig_zag_search(struct TreeNode *node, uint8_t cur_dir, size_t cur_len, size_t *max_len)
{
    if (node == NULL)
    {
        *max_len = cur_len > *max_len ? cur_len : *max_len;
        return;
    } 
    if (cur_dir == LEFT)
    {
        zig_zag_search(node->left, LEFT, 0, max_len);
        zig_zag_search(node->right, RIGHT, cur_len + 1, max_len);
    }
    else if (cur_dir == RIGHT)
    {
        zig_zag_search(node->left, LEFT, cur_len + 1, max_len);
        zig_zag_search(node->right, RIGHT, 0, max_len);
    }
    else 
    {
        zig_zag_search(node->left, LEFT, 0, max_len);
        zig_zag_search(node->right, RIGHT, 0, max_len);
    }
}

int longestZigZag(struct TreeNode* root) 
{
    size_t max_len = 0;
    zig_zag_search(root, ROOT, 0, &max_len);
    return max_len;
}