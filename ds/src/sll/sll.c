/*********************************
 * Reviewer: Daniel.b
 * Author: yisrael fisch       
 * File: sll.c
 * ******************************/

#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc, free*/
#include <assert.h>
#include "sll.h"

struct node
{
	void *data;
	struct node *next;
};

struct sll
{
	node_t *head;
	node_t *tail;

};

sll_iterator SLLBegin(sll_t *slist)
{
	assert(slist);
	return slist->head;
}

sll_iterator SLLEnd(sll_t *slist)
{
	assert(slist);
 	return slist->tail;
}

sll_iterator SLLNext(sll_iterator curr)
{
	assert(curr);
	return curr->next;
}

void *SLLGet(sll_iterator curr)
{
	assert(curr);
	return (curr->data);
}

void SLLSetData(sll_iterator curr, void *data)
{
	assert(curr);
	assert(data);
	curr->data = data;
}

int SLLIteratorsIsEqual(sll_iterator iter1, sll_iterator iter2)
{
	assert(iter1);
	assert(iter2);

	if(iter1 == iter2)
	{
		return 1;
	}
	
	return 0;
	
}

sll_t *SLLCreate()
{
	sll_t *slist = 0;
	node_t *tail = (node_t *)malloc(sizeof(node_t));
	if (NULL == tail)
	{
		printf("node_t allocation failed \n");
		return NULL;
	}

	slist = (sll_t *)malloc(sizeof(sll_t));
	if (NULL == tail)
	{
		printf("sll_t allocation failed \n");
		free(tail);
		return NULL;
	}
	
	tail->data = (void *)slist;
	tail->next = NULL;

	slist->head = tail;
	slist->tail = tail;

	return slist;
}

sll_iterator SLLInsert(sll_iterator curr, void *new_data)
{

	node_t *new_node = (node_t *)malloc(sizeof(node_t));

	assert(curr);
	assert(new_data);

	if (NULL == new_node)
	{
		while(NULL != curr->next)
		{
			curr = curr->next;
		}

		return curr;
	}
	
	new_node->data = curr->data;
	new_node->next = curr->next;

	curr->data = new_data;
	curr->next = new_node;

	if(NULL == new_node->next)
	{
		((sll_t *)new_node->data)->tail = new_node;		
	}

	return curr;
}


sll_iterator SLLRemove(sll_iterator curr)
{
	node_t *temp = curr->next;
	assert(curr);
	if(NULL == curr->next)
	{
		return curr;
	}

	curr->data = temp->data;
    curr->next = temp->next;
	free(temp);

	if(NULL == curr->next)
	{
		((sll_t *)curr->data)->tail = curr;
	}
		
	

	return curr;
}

size_t SLLCount(const sll_t *slist)
{
	size_t counter = 0;
	sll_iterator temp = slist->head;
	
	assert(slist);
	
	while(NULL != temp->next)
	{
		++counter;
		temp = temp->next;
			
	}
	return counter;
}

sll_iterator SLLFind(sll_iterator from, sll_iterator to,void *param, int (*match)(sll_iterator curr,void *param))
{
	assert(match);
	assert(from);
	assert(to);
	assert(param);
	while(from != to && !(0 == match(from, param)))
	{

			from = from->next;
		
	}

	return from;
}

int SLLForEach(sll_iterator from, sll_iterator to, void *param, int (*action)(sll_iterator curr,void *param))
{
	int status = 0;
	assert(action);
	assert(from);
	assert(to);
	assert(param);
	
	while(from->next != to->next && 0 == status)
	{
		status = action(from, param);
			
		from = from->next;	
		
	}

	return status;
}

void SLLDestroy(sll_t *slist)
{
	assert(slist);
	
	while(NULL != slist->head->next)
	{
		SLLRemove(slist->head);
	}
	free(slist->head);
	free(slist);
}

sll_t *SLLAppend(sll_t *slist1, sll_t *slist2)
{
	assert(slist1);
	assert(slist2);

	slist1->tail->next = slist2->head;
	slist2->head = slist1->head;
	SLLRemove(slist1->tail);

	free(slist1);
	return(slist2);
}



