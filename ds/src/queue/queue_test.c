/*********************************
 * Reviewer: irit ofir
 * Author: yisrael fisch       
 * File: queue_test.c
 * ******************************/

#include <stdio.h>/*printf*/
#include "queue.h"

void CheckQueueCreateQueueEnQueue();
void CheckQueueSize();
void CheckQueueIsEmpty();
void CheckQueueDeQueueQueuePeek();
void TestQAppend();

int main()
{
	CheckQueueCreateQueueEnQueue();
	CheckQueueSize();
	CheckQueueIsEmpty();
	CheckQueueDeQueueQueuePeek();
	TestQAppend();
	return 0;
}

void CheckQueueCreateQueueEnQueue()
{
	int *px = 0;
	int x = 3;
	int insert_check = 2;
	queue_t *check = QueueCreate();
	if(NULL == check)
	{
		printf("QueueCreate failed\n");
	}
	else
	{
		printf("QueueCreate succeeded\n");	
	}
	insert_check = QueueEnQueue(check, &x);
	if(0 == insert_check)
	{
		printf("QueueEnQueue succeeded\n");
	}
	if(1 == insert_check)
	{
		printf("QueueEnQueue failed\n");
	}

	px = (int *)QueuePeek(check);
	printf("value stord is: %d\n" , *px);
	QueueDestroy(check);
}

void CheckQueueSize()
{
	int x = 3;
	size_t size = 2;
	queue_t *check = QueueCreate();
	size = QueueSize(check);
    if(0 == size)
    {
   		printf("QueueSize succeeded \n");
	}
	else
	{
		printf("QueueSize failed \n");
	}
	/*after inserting*/
	QueueEnQueue(check, &x);
	size = QueueSize(check);
    if(1 == size)
    {
   		printf("QueueSize succeeded \n");
	}
	else
	{
		printf("QueueSize failed \n");
	}
	QueueDestroy(check);
}

void CheckQueueIsEmpty()
{
	
	int x = 3;
	int empty =2;
	queue_t *check = QueueCreate();
	empty = QueueIsEmpty(check);
	if(1 == empty)
    {
   		printf("QueueIsEmpty succeeded \n");
	}
	else
	{
		printf("QueueIsEmpty failed \n");
	}
	/*after inserting*/
	QueueEnQueue(check, &x);
	empty = QueueIsEmpty(check);
	if(0 == empty)
    {
   		printf("QueueIsEmpty succeeded \n");
	}
	else
	{
		printf("QueueIsEmpty failed \n");
	}
	QueueDestroy(check);
}


void CheckQueueDeQueueQueuePeek()
{
	int *px = 0;
	int x = 3;
	int y = 4;
	queue_t *check = QueueCreate();
	QueueEnQueue(check, &x);
	px = (int *)QueuePeek(check);
	printf("first value after 1 insert is: %d\n" , *px);
	QueueEnQueue(check, &y);
	px = (int *)QueuePeek(check);
	printf("first value after 2 insert is: %d\n" , *px);
	QueueDeQueue(check);
	px = (int *)QueuePeek(check);
	printf("first value after 1 remove is: %d\n" , *px);

	QueueDestroy(check);
}

void TestQAppend()
{
	queue_t *q1=QueueCreate();
	queue_t *q2=QueueCreate();

	int a=1;
	int b=2;
	int c=3;

	QueueEnQueue(q1, &a);
	QueueEnQueue(q1, &b);
	QueueEnQueue(q1, &c);


	QueueEnQueue(q2, &c);
	QueueEnQueue(q2, &b);
	QueueEnQueue(q2, &a);

	QueueAppend(q1,q2);

	if(6 == QueueSize(q1))
	{
		printf("QueueAppend succeeded");
	}
	else
	{
		printf("QueueAppend failed");
	}

	QueueDestroy(q1);

}

