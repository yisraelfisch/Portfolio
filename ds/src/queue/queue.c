/*********************************
 * Reviewer: irit ofir
 * Author: yisrael fisch       
 * File: queue.c
 * ******************************/

#include <stdlib.h>/*malloc, free*/
#include <stdio.h>/*printf*/
#include <assert.h>
#include "queue.h"
#include "sll.h"

struct queue
{
   sll_t *slist;
};

queue_t *QueueCreate()
{
 /*allocate memory for queue and then call SLLCreate
  and store it in queue->slist*/
	
	queue_t *q = (queue_t *)malloc(sizeof(queue_t));
	if (NULL == q)
	{
		printf("queue_t allocation failed \n");
		return NULL;
	}

	q->slist = SLLCreate();
	if(NULL == q->slist)
	{
		printf("slist allocation failed \n");
		free(q);
		return NULL;
	}

	return q;
}

void QueueDestroy(queue_t *q)
{
	/*destroys what slist pointing to and then destroy q*/
	assert(q);
	SLLDestroy(q->slist);
	q->slist=NULL;
	free(q);
	q=NULL;
}

int QueueEnQueue(queue_t *q, void *element_add)
{
	node_t *temp = 0;
	assert(q);
	assert(element_add);
	temp = SLLInsert((SLLEnd(q->slist)), element_add);
	if((SLLEnd(q->slist) == temp))
	{
		return 1;
	}
	return 0;
}

void QueueDeQueue(queue_t *q)
{
	assert(q);
	SLLRemove((SLLBegin(q->slist)));
}

void *QueuePeek(const queue_t *q)
{
	assert(q);
	return (SLLGet((SLLBegin(q->slist))));
}

queue_t *QueueAppend(queue_t *q1, queue_t *q2)
{
	assert(q1);
	assert(q2);

	q1->slist = SLLAppend(q1->slist, q2->slist);

	free(q2);	
	return q1;
}

size_t QueueSize(const queue_t *q)
{
	assert(q);
	return (SLLCount(q->slist));
}

int QueueIsEmpty(const queue_t *q)
{
	assert(q);
	return ((SLLEnd(q->slist) == (SLLBegin(q->slist))? 1 : 0));
}