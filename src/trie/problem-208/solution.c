/*      208. Implement Trie (Prefix Tree)

A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and retrieve keys in a dataset of strings. 
There are various applications of this data structure, such as autocomplete and spellchecker.

Implement the Trie class:

Trie() Initializes the trie object.
void insert(String word) Inserts the string word into the trie.
boolean search(String word) Returns true if the string word is in the trie (i.e., was inserted before), and false otherwise.
boolean startsWith(String prefix) Returns true if there is a previously inserted string word that has the prefix prefix, and false otherwise.
*/

#include <errno.h> 
#define LETTERS_CNT 26
#define UTF8_TABLE_OFFSET 97
#define ROOT_NODE ^

typedef struct Node Node;
typedef struct Trie Trie;

struct Node
{
    char val;
    bool end_of_word;
    Node *next_nodes[LETTERS_CNT];
};

struct Trie
{
    Node *root;
};

static size_t char_to_index(char c)
{
    return (size_t) (c - UTF8_TABLE_OFFSET);
}

static Node *create_node(char val)
{
    Node * new_node = (Node*)malloc(sizeof(Node));
    if (!new_node)
    {
        printf("Value of errno: %d\n", errno);
        return NULL;
    }

    new_node->val = val;
    new_node->end_of_word = false;
    memset(new_node->next_nodes, 0, LETTERS_CNT * sizeof(Node *));
  
    return new_node;
}

static void trie_insert_recursive(Node *node, char const *word, size_t word_index, size_t word_len)
{
    if (!node)
    {
        return;
    }
  
    if (word_index >= word_len)
    {
        node->end_of_word = true;
        return;
    }

    size_t index     = char_to_index(word[word_index]);
    Node *new_node   = NULL;
    Node *next_node  = node->next_nodes[index];

    if (!next_node)
    {
        new_node = create_node(word[word_index]);
        node->next_nodes[index] = new_node;
        trie_insert_recursive(new_node, word, word_index + 1, word_len);
    }
    else
    {
        trie_insert_recursive(next_node, word, word_index + 1, word_len);
    }
}

static bool trie_search_prefix_recursive(Node *node, char const *prefix, size_t prefix_index, size_t prefix_len)
{
    if (prefix_index >= prefix_len)
        return true;

    size_t index     = char_to_index(prefix[prefix_index]);
    Node *next_node  = node->next_nodes[index];
    
    if (next_node)
    {
        return trie_search_prefix_recursive(next_node, prefix, prefix_index + 1, prefix_len);
    }
    else
    {
        return false;
    }
}

static bool trie_search_recursive(Node *node, char const *word, size_t word_index, size_t word_len)
{
    if (word_index < word_len)
    {
        size_t index     = char_to_index(word[word_index]);
        Node *next_node  = node->next_nodes[index];
        if (next_node)
            return trie_search_recursive(next_node, word, word_index + 1, word_len);
        else 
            return false;
    } 
    else
    {
        if (node->end_of_word)
            return true;
        else
            return false;
    }
}

static void trie_node_free_recursive(Node *node)
{
    for (size_t i = 0; i < LETTERS_CNT; i++)
    {
        if (node->next_nodes[i] != NULL)
            trie_node_free_recursive(node->next_nodes[i]);
    }
    free(node);
}

Trie *trieCreate()
{
    Trie *new_trie = (Trie*)malloc(sizeof(Trie));
    if (!new_trie)
    {
        printf("Value of errno: %d\n", errno);
        return NULL;
    }
  
    new_trie->root = create_node('ROOT_NODE');
    return new_trie;
}

void trieInsert(Trie *obj, char const *word)
{
    if (!obj)
    {
        printf("Value of errno: %d\n", errno);
        return;
    }

    size_t word_len = strlen(word);
    trie_insert_recursive(obj->root, word, 0, word_len);
}

bool trieSearch(Trie *obj, char const *word)
{
    if (!obj)
    {
        printf("Value of errno: %d\n", errno);
        return false;
    }    
  
    size_t word_len = strlen(word);
    return trie_search_recursive(obj->root, word, 0, word_len);
}

bool trieStartsWith(Trie *obj, char const *prefix) 
{
    if (!obj)
    {
        printf("Value of errno: %d\n", errno);
        return false;
    }
  
    size_t prefix_len = strlen(prefix);
    return trie_search_prefix_recursive(obj->root, prefix, 0, prefix_len);
}

void trieFree(Trie *obj)
{
    trie_node_free_recursive(obj->root);
    free(obj);
}

static void dfs_print_trie(Node const *node)
{
    for (size_t i = 0; i < LETTERS_CNT; i++)
    {
        if (node->next_nodes[i] != NULL)
        {
            printf("%c ",node->next_nodes[i]->val);
            dfs_print_trie(node->next_nodes[i]);
        }
    }
    printf("\n");
}

/**
 * Your Trie struct will be instantiated and called as such:
 * Trie* obj = trieCreate();
 * trieInsert(obj, word);
 
 * bool param_2 = trieSearch(obj, word);
 
 * bool param_3 = trieStartsWith(obj, prefix);
 
 * trieFree(obj);
*/
