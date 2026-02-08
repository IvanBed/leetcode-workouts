/*
				1161. Maximum Level Sum of a Binary Tree

Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.

Return the smallest level x such that the sum of all the values of nodes at level x is maximal.

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/*
My attempt to implement a soluton from scratch
*/
  
#define true 1
#define false 0


typedef struct node node;
typedef struct TreeNode TreeNode;

struct node
{
    TreeNode *val;
    node *next;
    node *prev;
    size_t level;
};

typedef struct
{
    node *head;
    node *tail;
    size_t size;
} queue;

node *create_node(TreeNode  *val, size_t level)
{
    node * new_node = (node*) malloc(sizeof(node));
    if (!new_node)
    {
        return NULL;
    }
    new_node->val = val;
    new_node->level = level;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;   
}

int init_queue(queue **queue_inst)
{
    *queue_inst = (queue*) malloc(sizeof(queue));
    if (!queue_inst)
    {
        return false;
    }
    (*queue_inst)->tail = NULL;
    (*queue_inst)->head = NULL;
    (*queue_inst)->size = 0;
    return true;
}

void delete_queue(queue *queue_inst)
{
    node *cur = queue_inst->tail;
    node *temp = NULL;
    while (cur)
    {
        temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(temp);
}

int queue_empty(queue *queue_inst)
{
    if (queue_inst->size == 0 || 
            queue_inst->tail == NULL && queue_inst->head == NULL)
        return true;
    else
        return false;
}

int add_element(queue *queue_inst, TreeNode  *val, size_t level)
{
    node * new_node = create_node(val, level);
    queue_inst->size++;
    if (!queue_empty(queue_inst))
    {
        queue_inst->tail->prev = new_node;
        new_node->next = queue_inst->tail;
        queue_inst->tail = new_node;
    }
    else
    {
        queue_inst->tail = new_node;
        queue_inst->head = new_node;
    }
    return 0;
}

TreeNode *get_element_value(queue *queue_inst, size_t *level)
{
    node *temp_tail = queue_inst->head;
    TreeNode *val   = queue_inst->head->val; 
    *level          = queue_inst->head->level;
    queue_inst->size--;
    if (queue_inst->tail == queue_inst->head)
    {
        queue_inst->tail = NULL;
        queue_inst->head = NULL;
    }
    else 
    {
        queue_inst->head = queue_inst->head->prev;
        if (queue_inst->head)
            queue_inst->head->next = NULL;
    }

    free(temp_tail);
    return val;
}

int maxLevelSum(struct TreeNode* root) 
{
    int max                  = root->val;
    int cur_level_val        = 0;
    
    size_t cur_node_level    = 1;
    size_t cur_tree_level    = 1;
    size_t min_level_max     = 1;
    
    queue *queue_inst        = NULL;
    TreeNode *cur_node       = NULL;
    
    if (!init_queue(&queue_inst))
    {
        printf("Can not allocate memory for queue!\n");
        return -1;
    }
    
    add_element(queue_inst, root, 1);
    
    do
    {
        cur_node = get_element_value(queue_inst, &cur_node_level);
        if (cur_node_level == cur_tree_level)
        {
            cur_level_val += cur_node->val;  
        }

        if (cur_node->left != NULL)
        {
            add_element(queue_inst, cur_node->left, cur_node_level + 1);
        } 

        if (cur_node->right != NULL)
        {
            add_element(queue_inst, cur_node->right, cur_node_level + 1);
        } 
        
        if (cur_node_level != cur_tree_level || queue_empty(queue_inst))
        {
            if (max < cur_level_val)
            {
                min_level_max = cur_tree_level;
                max = cur_level_val;
            }           
            cur_tree_level = cur_node_level;
            cur_level_val = cur_node->val;  
        }

    }  while(!queue_empty(queue_inst));

    delete_queue(queue_inst);
    
    return min_level_max;
}