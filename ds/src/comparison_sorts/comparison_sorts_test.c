/*********************************
 * Reviewer: avigail
 * Author: yisrael fisch       
 * File: comparison_sorts_test.c
 * ******************************/


#include <stdlib.h> /*malloc free*/
#include <stdio.h> /*printf*/
#include <time.h>

#include "comparison_sorts.h"

static int CmpFunc(const void *a, const void *b);

int *CreateArr(int *ptr, size_t size);
int *InitArr(int *ptr, size_t size);
void PrintArr(int *ptr, size_t size);

void InsertionSortTest();
void SelectionSortTest();
void BubbleSortTest();

int main(int argc, char const **argv)
{
/*	InsertionSortTest();
	BubbleSortTest();
	SelectionSortTest();*/

	int *ptr = NULL;
	size_t size = atoi(argv[2]);

	ptr = CreateArr(ptr, size);
	ptr = InitArr(ptr, size);

	if(argc < 3)
	{
		printf("please enter sorting algo");
		exit(1);
	}

	switch (argv[1][0])
	{
		case 'q' :
			printf("qsort is choosen!\n");
			qsort(ptr, size, sizeof(int), CmpFunc);
			PrintArr(ptr, size);
			break;

		case 'b' :
			printf("BubbleSort is choosen!\n");
			BubbleSort(ptr, size);
			PrintArr(ptr, size);
			break;

		case 'i' :
			printf("InsertionSort is choosen!\n");
			InsertionSort(ptr, size);
			PrintArr(ptr, size);
			break;

		case 's' :
			printf("SelectionSort is choosen!\n");
			SelectionSort(ptr, size);
			PrintArr(ptr, size);
			break;
	}

	free(ptr);

	return 0;
}

static int CmpFunc(const void *a, const void *b) 
{
   return ( *(int*)a - *(int*)b);
}


void InsertionSortTest()
{
	int *ptr = NULL;
	size_t size = 5000;

	ptr = CreateArr(ptr, size);
	ptr = InitArr(ptr, size);

	PrintArr(ptr, size);

	InsertionSort(ptr, size);

	PrintArr(ptr, size);

	free(ptr);

}

void SelectionSortTest()
{
	int *ptr = NULL;
	size_t size = 5000;

	ptr = CreateArr(ptr, size);
	ptr = InitArr(ptr, size);

	PrintArr(ptr, size);

	SelectionSort(ptr, size);

	PrintArr(ptr, size);

	free(ptr);
}

void BubbleSortTest()
{
	int *ptr = NULL;
	size_t size = 5000;

	ptr = CreateArr(ptr, size);
	ptr = InitArr(ptr, size);

	PrintArr(ptr, size);

	BubbleSort(ptr, size);

	PrintArr(ptr, size);

	free(ptr);
}



int *CreateArr(int *ptr, size_t size)
{
	ptr = (int *)malloc(sizeof(int) * size);
	if(!ptr)
	{
		printf("Allocation Failed");
		return NULL;
	}

	return ptr;
}

int *InitArr(int *ptr, size_t size)
{
	int i = 0;

	for(i = 0; i < (int)size; ++i)
	{
		ptr[i] = (rand() % 7000);
	}

	return ptr;
}

void PrintArr(int *ptr, size_t size)
{
	int i = 0;
	/*srand((unsigned)time(&t));*/

	for(i = 0; i < (int)size; ++i)
	{
		if(i % 1000 == 0)
		{
			printf("%d ," ,ptr[i]);
		}

	}
	printf("\n\n\n\n\n\n");
}
