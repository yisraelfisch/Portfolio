#include "sll_exercises.h"
#include <stdio.h>
#include <stdlib.h>

void TestFlip();
void TestHasLoop();
void TestFindIntersection();
int main()
{
	TestFlip();
	TestHasLoop();
	TestFindIntersection();
	return 0;
}

void TestFlip()
{
	node_t *temp = NULL;
	node_t *node1 = (node_t *)malloc(sizeof(node_t));
	node_t *node2 = (node_t *)malloc(sizeof(node_t));
	node_t *node3 = (node_t *)malloc(sizeof(node_t));
	
	node1->data = (int *)1;
	node2->data = (int *)2;
	node3->data = (int *)3;
	
	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;
	
	temp = node1;
	printf("list values before reverse:\n");
	
	while(temp != NULL)
	{
		printf("%ld\n", (size_t)temp->data);
		temp = temp->next;
	}
	
	node1 = Flip(node1);
	printf("list values after reverse:\n");
	
	while(node1 != NULL)
	{
		printf("%ld\n", (size_t)node1->data);
		node1 = node1->next;
	}
}

void TestHasLoop()
{
	int res = 0;
	node_t *node1 = (node_t *)malloc(sizeof(node_t));
	node_t *node2 = (node_t *)malloc(sizeof(node_t));
	node_t *node3 = (node_t *)malloc(sizeof(node_t));
	node_t *node4 = (node_t *)malloc(sizeof(node_t));
	
	node1->data = (int *)1;
	node2->data = (int *)2;
	node3->data = (int *)3;
	node4->data = (int *)4;
	
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = NULL;
	
	res = HasLoop(node1);
	if(0 == res)
	{
		printf("No loop was found\n");
	}
	else
	{
		printf("A loop was found\n");
	}
	
	node4->next = node1;
	
	res = HasLoop(node1);
	if(0 == res)
	{
		printf("No loop was found\n");
	}
	else
	{
		printf("A loop was found\n");
	}
}

void TestFindIntersection()
{
	node_t *temp = NULL;
	node_t *node1 = (node_t *)malloc(sizeof(node_t));
	node_t *node2 = (node_t *)malloc(sizeof(node_t));
	node_t *node3 = (node_t *)malloc(sizeof(node_t));
	node_t *node4 = (node_t *)malloc(sizeof(node_t));
	node_t *node5 = (node_t *)malloc(sizeof(node_t));
	
	node1->data = (int *)1;
	node2->data = (int *)2;
	node3->data = (int *)3;
	node4->data = (int *)4;
	node5->data = (int *)5;
	
	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;
	node4->next = node5;
	node5->next = node3;
	
	temp = FindIntersection(node1, node2);
	
	if(temp != NULL)
	{
		printf("Intersection was found, the value is: %ld\n", (size_t)temp->data);
	}
	else
	{
		printf("No intersection was found\n");
	}
}
