/*********************************
 * Reviewer: 
 * Author:     
 * File: bst.c
 * ******************************/

#include <stdlib.h> /*malloc, free*/
#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/
#include "bst.h"


typedef struct bst_node
{
	void *data;
	struct bst_node *parent;
	struct bst_node *child[2];/*0 - left, 1- right*/
}bst_node_t;

struct bst
{
	struct bst_node* root;
	bst_compare_func_t compare_func;
	void *user_param;
};

/*check if curr is the right or left child*/
static  int BSTCheckWhichChild(bst_node_t *curr);

/*assigned the value of the child to the parent*/
static void SwapParent(bst_node_t *parent, bst_node_t *child);

static void RemoveNode(bst_node_t *bst_node);

bst_t *BSTCreate(bst_compare_func_t compare_func, void *user_param)
{
	bst_t *bst = NULL;
	
	assert(compare_func);

	
	bst = (bst_t *)malloc(sizeof(bst_t));
	if(!bst)
	{
		return NULL;
	}
	bst->root = (bst_node_t *)malloc(sizeof(bst_node_t));
	if(!bst->root)
	{
		free(bst);
		return NULL;
	}

	bst->compare_func = compare_func;
	bst->user_param = user_param;
	bst->root->data = NULL; 
	bst->root->parent = NULL;
	bst->root->child[0] = NULL;
	bst->root->child[1] = NULL;

	return bst;
}

void BSTDestroy(bst_t *bst)
{
	/*bst_iterator_t curr;*/
	assert(bst);

	while(!BSTIsEmpty(bst))
	{
		/*curr.bst_node = bst->root;
		BSTRemove(curr);*/
		BSTRemove(BSTBegin(bst));
	}
	
	RemoveNode(bst->root);
	
	bst->root = NULL;
	bst->compare_func = NULL;
	bst->user_param = NULL;
	free(bst);
	bst = NULL;

}

bst_iterator_t BSTInsert(bst_t *bst, const void *data)
{

	bst_node_t *temp = NULL;
	bst_node_t *new_node = NULL;
	bst_node_t *dummy = NULL;
	bst_iterator_t new_iter;
	int compare_res = 0;
	int child_index = 0;
	
	assert(bst);
	assert(data);

	temp = bst->root;
	
	if(BSTIsEmpty(bst))
	{
		dummy = (bst_node_t *)malloc(sizeof(bst_node_t));
		if(!dummy)
		{

			return BSTEnd(bst);
		}

		dummy->data = NULL;
		dummy->parent = bst->root;
		dummy->child[0] = NULL;
		dummy->child[1] = NULL;
		
		temp->data = (void *)data;
		temp->child[1] = dummy;
		new_iter.bst_node = temp;
		return new_iter;
	}
	
	new_node = (bst_node_t*)malloc(sizeof(bst_node_t));
	if(!new_node)
	{
		return (BSTEnd(bst));
	}
    /*check if the node allready exist*/
	compare_res = bst->compare_func(temp->data, data, bst->user_param);
	if(0 == compare_res)
	{
		free(new_node);
		return (BSTEnd(bst));
	}
	
	
	/*check if the key is biger/smaller then corrent node key*/
	child_index = compare_res > 0 ;		
	
	while((temp->child[child_index]) && (temp->child[child_index])->data != NULL)
	{

		temp = temp->child[child_index];
		compare_res = bst->compare_func(temp->data, data, bst->user_param);
	
		if(0 == compare_res)
		{
			free(new_node);
			return (BSTEnd(bst));
		}

		child_index = compare_res > 0 ;
	}
		
	new_node->data = (void *)data;
	new_node->parent = temp;
	new_node->child[0] = NULL;
	
	if(!(temp->child[child_index])) /*child is null*/
	{
		new_node->child[1] = NULL;
		temp->child[child_index] = new_node;
	}
	else
	{											/*child is dummy, conect the dummy and the new node*/			
		temp->child[child_index]->parent = new_node;
		new_node->child[1] = temp->child[child_index];
		temp->child[child_index] = new_node;
	}

	new_iter.bst_node = new_node;
	return new_iter;


}

bst_iterator_t BSTFind(bst_t *bst, const void *data)
{
	bst_node_t *temp = NULL;
	bst_iterator_t new_iter;
	int compare_res = 0;
	int child_index = 0;

	assert(bst);
	assert(data);

	temp = bst->root;
	if(BSTIsEmpty(bst))
	{
		return (BSTEnd(bst));
	}

	compare_res = bst->compare_func(temp->data, data, bst->user_param);

	/*check if the key is biger/smaller/same then corrent node key*/
	
	child_index = compare_res > 0 ;	
	/*check if we found the node or there is a next one to compare*/

	while((temp->child[child_index]) && (temp->child[child_index])->data != NULL && 0 != compare_res)
	{
		temp = temp->child[child_index];
		compare_res = bst->compare_func(temp->data, data, bst->user_param);
	
		child_index = compare_res > 0 ;
	}	

	if(0 == compare_res)
	{
		new_iter.bst_node = temp;
		return new_iter;
	}
	else                 /*nothing was found*/
	{
		return (BSTEnd(bst));
	}

}

int BSTForEach(bst_t *bst, bst_action_func_t action_func, void *param)
{
	bst_iterator_t curr_iter;
	size_t status = 0;

	assert(bst);
	assert(action_func);

	curr_iter = BSTBegin(bst);

	while(0 == BSTIsSameIter(curr_iter,BSTEnd(bst)))
	{
		
        if(0 != (status = action_func(curr_iter.bst_node->data, param)))
        {
            return status;
        }
		curr_iter = BSTNext(curr_iter);
	}
	return status;	
}

int BSTIsEmpty(bst_t *bst)
{
	assert(bst);
	return (((bst->root)->data == NULL)? 1:0);
}


bst_iterator_t BSTBegin(bst_t *bst)
{
	bst_node_t *temp = NULL;
	bst_iterator_t begin_iter;
	assert(bst);

	temp = bst->root;

	while(temp->child[0])
	{
		temp = temp->child[0];
	}
	begin_iter.bst_node = temp;
	return begin_iter;
}

bst_iterator_t BSTEnd(bst_t *bst)
{
	bst_node_t *temp = NULL;
	bst_iterator_t end_iter;
	assert(bst);

	temp = bst->root;

	while(temp->child[1])
	{
		temp = temp->child[1];
	}
	end_iter.bst_node = temp;
	return end_iter;
}

/*if there is a right child i check and the check agein to th left*/
bst_iterator_t BSTNext(bst_iterator_t iter)
{
	bst_node_t *curr = NULL;
	curr = iter.bst_node;

	if(curr->child[1])
	{
		curr = curr->child[1];
		while(curr->child[0])
		{
			curr = curr->child[0];
		}
		iter.bst_node = curr;
		return iter;		

	}
	else /*if there is no child i check for a parent biggger then the curr*/
	{
		while(curr->parent && curr == curr->parent->child[1])
		{
			curr = curr->parent;
		}
		iter.bst_node = curr->parent;
		return iter;		

	}

}

bst_iterator_t BSTPrev(bst_iterator_t iter)
{
	bst_node_t *curr = NULL;
	curr = iter.bst_node;

	if(curr->child[0])
	{
		curr = curr->child[0];
		while(curr->child[1])
		{
			curr = curr->child[1];
		}
		iter.bst_node = curr;
		return iter;		

	}
	else 
	{
		while(curr->parent && curr == curr->parent->child[0])
		{
			curr = curr->parent;
		}
		iter.bst_node = curr->parent;
		return iter;		

	}

}

int BSTIsSameIter(bst_iterator_t f_iter, bst_iterator_t s_iter)
{
	return ((f_iter.bst_node == s_iter.bst_node) ? 1 : 0);
}

size_t BSTSize(bst_t *bst)
{
	bst_iterator_t count_iter;
	size_t counter = 0;
	assert(bst);

	count_iter = BSTBegin(bst);

	while(0 == BSTIsSameIter(count_iter,BSTEnd(bst)))
	{
		++counter;
		count_iter = BSTNext(count_iter);
	}
	return counter;
}

void BSTRemove(bst_iterator_t iter)
{
	bst_node_t *curr = NULL;
	bst_node_t *parent = NULL;
	bst_node_t *child = NULL;
	bst_node_t *left_child = NULL;
	int index = 0;
	
	curr = iter.bst_node;
	parent = curr->parent;
	
	if(parent)/*if there is a parent check if curr left/right child*/
	{
		index = BSTCheckWhichChild(curr);
	}

	/*if curr have no child*/
	if(!(curr->child[0]) && !(curr->child[1]))
	{
		if(parent)
		{
			parent->child[index] = NULL;
		}

		RemoveNode(curr);
	}
	else if(!(curr->child[0]) || !(curr->child[1]))
	{
		if(curr->child[0])			/*if curr have left child*/
		{
			curr->child[0]->parent = curr->parent;
			if(parent)
			{
				curr->parent->child[index] = curr->child[0];
				RemoveNode(curr);
			}
			if(!parent)		/*if curr is the root assign the child to furr and remove child*/
			{
				child = curr->child[0];
				SwapParent(curr, child);
				RemoveNode(child);
			}
		}
		else if(curr->child[1])  /*if curr have right child*/
		{
			curr->child[1]->parent = curr->parent;
			if(parent)
			{
				curr->parent->child[index] = curr->child[1];
				RemoveNode(curr);
			}
			if(!parent)		/*if curr is the root assign the child to furr and remove child*/
			{
				child = curr->child[1];
				SwapParent(curr, child);
				RemoveNode(child);
			}
		}
		
	}			
	else if((curr->child[0]) && (curr->child[1])) /*if curr have two childs move the left child up 
																		and conect to right child*/
	{
			curr->child[0]->parent = curr->parent;

			left_child = curr->child[0];
			while(left_child->child[1])
			{
				left_child = left_child->child[1];
			}
			curr->child[1]->parent = left_child;
			left_child->child[1] = curr->child[1];

			if(parent)
			{
				curr->parent->child[index] = curr->child[0];
				RemoveNode(curr);
			}
			if(!parent)
			{
				child = curr->child[0];		/*if curr is the root assign the child to furr and remove child*/
				SwapParent(curr, child);
				RemoveNode(child);
			}
			
	}

}


void *BSTGetData(bst_iterator_t iter)
{
		return iter.bst_node->data;
}


static  int BSTCheckWhichChild(bst_node_t *curr)
{
	return ((curr == curr->parent->child[1])? 1:0);
}

static void SwapParent(bst_node_t *parent, bst_node_t *child)
{
	parent->data = child->data;
	parent->child[0] = child->child[0];
	parent->child[1] = child->child[1];
	if(parent->child[0])
	{
		parent->child[0]->parent = parent;
	}

	if(parent->child[1])
	{
		parent->child[1]->parent = parent;
	}
	/*parent->parent = child->parent;*/
}

static void RemoveNode(bst_node_t *bst_node)
{
	bst_node->data = NULL;
	bst_node->child[0] = NULL;
	bst_node->child[1] = NULL;
	bst_node->parent = NULL;
	free(bst_node);
	bst_node = NULL;
}
