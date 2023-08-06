/***************************
Author: 
Reviwer: 
File: linear_sorts.c
***************************/
#include <stdlib.h> /*malloc free*/
#include <stdio.h>
#include <time.h>

#include "linear_sorts.h"

static int CmpFunc(const void *a, const void *b);

int *CreateArr(int *ptr, size_t size);
int *InitArr(int *ptr, size_t size);
void PrintArr(int *ptr, size_t size);

int main(int argc, char const **argv)
{
	int *ptr = NULL;
	size_t size = atoi(argv[2]);

	ptr = CreateArr(ptr, size);
	ptr = InitArr(ptr, size);

	if(argc < 3)
	{
		printf("please enter the first letter  of the sorting algo + num of elements");
		exit(1);
	}

	switch (argv[1][0])
	{
		case 'c' :
			printf("CountingSort is choosen!\n");
			CountingSort(ptr, size);
			PrintArr(ptr, size);
			break;

   	case 'r' :
			printf("RadixSort is choosen!\n");
			RadixSort(ptr, size);
			PrintArr(ptr, size);
			break;

		case 'q' :
			printf("qsort is choosen!\n");
			qsort(ptr, size, sizeof(int), CmpFunc);
			PrintArr(ptr, size);
			break;

		default: 
			printf("please enter the first letter  of the sorting algo + num of elements");
			
	}

	free(ptr);

	return 0;
}

static int CmpFunc(const void *a, const void *b) 
{
   return ( *(int*)a - *(int*)b);
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

	/*time_t time = time(NULL);*/

	/*srand((unsigned)time(&t));*/
	/*for count sort put % 100, for radix sort put % 1000000*/
	for(i = 0; i < (int)size; ++i)
	{
		ptr[i] = (rand() %10000000);
	}

	return ptr;
}

void PrintArr(int *ptr, size_t size)
{
	int i = 0;
	/*srand((unsigned)time(&t));*/

	for(i = 0; i < (int)size; ++i)
	{
		if(i % 100 == 0)
		{
			printf("%d ," ,ptr[i]);
		}
	}
	printf("\n\n\n\n\n\n");
	
}
