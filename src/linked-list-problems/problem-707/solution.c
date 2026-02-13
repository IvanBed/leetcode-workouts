/*
Design your implementation of the linked list. You can choose to use a singly or doubly linked list.
A node in a singly linked list should have two attributes: 
val and next. val is the value of the current node, and next is a pointer/reference to the next node.
If you want to use the doubly linked list, you will need one more attribute prev to indicate the previous node in the linked list. 
Assume all nodes in the linked list are 0-indexed.

Implement the MyLinkedList class:

MyLinkedList() Initializes the MyLinkedList object.
int get(int index) Get the value of the indexth node in the linked list. If the index is invalid, return -1.
void addAtHead(int val) Add a node of value val before the first element of the linked list. 
After the insertion, the new node will be the first node of the linked list.
void addAtTail(int val) Append a node of value val as the last element of the linked list.
void addAtIndex(int index, int val) Add a node of value val before the indexth node in the linked list. 
If index equals the length of the linked list, the node will be appended to the end of the linked list. 
If index is greater than the length, the node will not be inserted.
void deleteAtIndex(int index) Delete the indexth node in the linked list, if the index is valid.

*/
//   tail n <- node n - 1 ... <- node 1 <- head 0
//   		->                ->        ->  
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define true  1
#define false 0

typedef struct Node Node;
typedef struct MyLinkedList MyLinkedList;
void print(MyLinkedList const*);

struct Node
{
    int64_t val;
    Node *next;
    Node *prev;
};

struct MyLinkedList 
{
    Node *head;
    Node *tail;
    size_t size;
};

static Node *create_node(int val)
{
    Node * new_node = (Node*) malloc(sizeof(Node));
    if (!new_node)
    {
        //err
        return NULL;
    }
    //default init    
    new_node->val   = val;
    new_node->next  = NULL;
    new_node->prev  = NULL;
    
	return new_node;
}

static void delete_node_from_list(MyLinkedList* obj, Node *node)
{
	//Node *temp_node = node;
	
	if (node == obj->head && node == obj->tail)
	{
	    obj->head = NULL;
	    obj->tail = NULL;
	}
	else if (node == obj->head)
	{
		obj->head = node->next;
		obj->head->prev = NULL;
	}
	else if (node == obj->tail)
	{
		obj->tail = node->prev;
		obj->tail->next = NULL;
	}
	else
	{
		if (node->prev) 
            node->prev->next = node->next;
		if (node->next) 
            node->next->prev = node->prev;
	}
	
	obj->size--;
	free(node);
}

static uint8_t empty(MyLinkedList const *obj)
{
	if (!obj) 
	{
		return false;
	}	
	
	if (obj->head == NULL || obj->tail == NULL && obj->size == 0)
		return true;
	else
		return false;
}

static Node *find_node(MyLinkedList const *obj, size_t index)
{
    if (!obj) 
	{
		return NULL;
	}	
	
	Node *current_node   = NULL;
	Node *target_node    = NULL;
	size_t current_index = 0;

	current_index = 0;
	current_node = obj->head;
	while (current_node)
	{
		if (current_index == index)
		{
			target_node = current_node;
			break;
		}
		current_node = current_node->next;
		current_index++;
	}

	return target_node;
}

static void add_node_before(MyLinkedList *obj, Node *l_node, int val)
{
	if (!obj) 
	{
		return;
	}
	
	Node * new_node = create_node(val);
	Node *r_node    = l_node->prev;
	
	if (new_node)
	{
		new_node->prev = r_node;
		new_node->next = l_node;
		if (r_node) r_node->next = new_node;
		if (l_node) l_node->prev = new_node;
	}
	obj->size++;
}

MyLinkedList *myLinkedListCreate() 
{
    MyLinkedList * new_linked_list_inst = (MyLinkedList *) malloc(sizeof(MyLinkedList));
    if (!new_linked_list_inst)
    {
        //err
        return NULL;
    }
    //default init
    new_linked_list_inst->head = NULL;
    new_linked_list_inst->tail = NULL;
    new_linked_list_inst->size = 0;
    return new_linked_list_inst;
}

int myLinkedListGet(MyLinkedList const *obj, int index) 
{
    if (!obj) 
	{
		return -1;
	}
	
	Node *target_node   = NULL;
	int target_node_val = -1;
	
	if (index < 0 || index > obj->size)
		return target_node_val;

    target_node = find_node(obj, index); 
	
	if (target_node) target_node_val = target_node->val;
	
	return target_node_val;
}

void myLinkedListAddAtHead(MyLinkedList* obj, int val)
{
    if (!obj) 
	{
		return;
	}    
	
	Node * new_node = create_node(val);
	if (new_node)
	{
		if (empty(obj))
		{
			obj->head = new_node;
			obj->tail = new_node;
		}
		else 
		{
			new_node->next = obj->head;
			obj->head->prev = new_node;
			obj->head = new_node;			
		}
		obj->size++;
	} 
    
}

void myLinkedListAddAtTail(MyLinkedList *obj, int val) 
{
    if (!obj) 
	{
		return;
	}    

	Node * new_node = create_node(val);
	if (new_node)
	{
		if (empty(obj))
		{
			obj->head = new_node;
			obj->tail = new_node;
		}
		else 
		{
		    new_node->prev = obj->tail;
			obj->tail->next = new_node;
			obj->tail = new_node;
		}
		obj->size++;
	}  
}

void myLinkedListAddAtIndex(MyLinkedList *obj, size_t index, int val) 
{
    if (!obj) 
	{
		return;
	}
	
    if (index > obj->size)
    {
        return;
    }
    
    if (index == obj->size)
    {
        myLinkedListAddAtTail(obj, val);
        return;
    }
    
	Node *target_node = NULL;
	target_node = find_node(obj, index); 
	
	if (target_node) 
	{
		if (target_node == obj->head) myLinkedListAddAtHead(obj, val);
		else add_node_before(obj, target_node, val);
	}
}

void myLinkedListDeleteAtIndex(MyLinkedList *obj, size_t index) 
{
    if (!obj) 
	{
		return;
	}
	
	Node *target_node   = NULL;
	if (index < 0 || index > obj->size)
		return;
	
	target_node = find_node(obj, index); 
	
	if (target_node) 
	{
		delete_node_from_list(obj, target_node);
	}	
}

void myLinkedListFree(MyLinkedList *obj) 
{
    Node *current_node 	= obj->head;
	Node *temp_node 	= NULL;
	while (current_node)
	{
		temp_node = current_node;
		current_node = current_node->next;
		free(temp_node);
		obj->size--;
	}
	free(obj);
}


/**
 * Your MyLinkedList struct will be instantiated and called as such:
 * MyLinkedList* obj = myLinkedListCreate();
 * int param_1 = myLinkedListGet(obj, index);
 
 * myLinkedListAddAtHead(obj, val);
 
 * myLinkedListAddAtTail(obj, val);
 
 * myLinkedListAddAtIndex(obj, index, val);
 
 * myLinkedListDeleteAtIndex(obj, index);
 
 * myLinkedListFree(obj);
*/
int main() 
{
	MyLinkedList *l_list = myLinkedListCreate();
	
	myLinkedListAddAtHead(l_list, 1);
	myLinkedListAddAtHead(l_list, 2);
	myLinkedListAddAtTail(l_list, 3);
	
	myLinkedListAddAtIndex(l_list, 3 ,4);
	
	print(l_list);
	
	
	myLinkedListFree(l_list);

}



/**
 * Your MyLinkedList struct will be instantiated and called as such:
 * MyLinkedList* obj = myLinkedListCreate();
 * int param_1 = myLinkedListGet(obj, index);
 
 * myLinkedListAddAtHead(obj, val);
 
 * myLinkedListAddAtTail(obj, val);
 
 * myLinkedListAddAtIndex(obj, index, val);
 
 * myLinkedListDeleteAtIndex(obj, index);
 
 * myLinkedListFree(obj);
*/