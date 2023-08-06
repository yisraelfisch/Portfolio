/*********************************
 * Reviewer: Irit				
 * Author: Daniel Binyamin			
 * File: sll_test.c				
 * ******************************/
#include <string.h>/*strcmp*/
#include <stdio.h>/*printf*/
#include "sll.h" 
int TestMatchString(sll_iterator curr,void *param);
int TestAction(sll_iterator curr,void *param);

void CheckCreateBegEndNext();
void CheckInsertGetIsEq();
void CheckRemoveSetData();
void CheckCountFind();
void CheckForeach();

int main()
{
    	
    	CheckCreateBegEndNext();
	CheckInsertGetIsEq();
	CheckRemoveSetData();
	CheckCountFind();
	CheckForeach();
	return 0;
}

void CheckCreateBegEndNext()
{
	void * check = 0;
	sll_iterator beg=0 , end=0;
	sll_t *sll = SLLCreate();
	
	beg = SLLBegin(sll);
	end = SLLEnd(sll);
	
	check = SLLGet(end); 
	if(!SLLIteratorsIsEqual(end ,beg))
	{
		printf("Create/Begin/End Error\n");
	}
	
	if(NULL != SLLNext(end))
	{
		printf("End Error\n");
	}
	
	if(NULL != SLLNext(beg))
	{
		printf("Begin Error\n");
	}
	
	if(sll != check)
	{
		printf("Data Error \n");
	}
	
	SLLDestroy(sll);

}

void CheckInsertGetIsEq()
{
	
	sll_iterator head=0 , tail=0 , iter=0;
	int a = 5 , b=4;
	sll_t *sll= SLLCreate();
	
	head = SLLBegin(sll); /*get head*/
	
	iter = SLLInsert(head, &a);/*insert element*/
	
	tail = SLLEnd(sll);	/*get new end*/
	
	if(SLLIteratorsIsEqual(head ,tail))/*check if eq*/
	{
		printf("Insert (1) Error\n");
	}
	
	if(a != *((int*)SLLGet(iter)))
	{
		printf("Insert (2) Error\n");	
	}
	
	iter = SLLInsert(iter, &b);
	
	if(b != *((int*)SLLGet(iter)))
	{
		printf("Insert (3) Error\n");
	}
	
	SLLDestroy(sll);
	
}


void CheckRemoveSetData()
{
	sll_iterator head=0 , tail=0 , iter=0;
	int a = 5 , b=4;
	sll_t *sll= SLLCreate();
	
	head = SLLBegin(sll); /*get head*/
	
	iter = SLLInsert(head, &a);
	iter = SLLInsert(iter, &b);
	SLLSetData(iter, &a);
	
	if(*((int*)SLLGet(iter))!= *((int*)SLLGet(head)))
	{
		printf("SetData (1) Error\n");	
	}
	iter = SLLInsert(head, &a);
	iter = SLLInsert(iter, &b);
	
	iter = SLLRemove(iter);
	iter = SLLRemove(iter);
	iter = SLLRemove(iter);
	iter = SLLRemove(iter);
	
	head = SLLBegin(sll);
	tail = SLLEnd(sll);	
	if(!SLLIteratorsIsEqual(head, tail))
	{
		printf("Remove Error\n");
	}	
	
	SLLDestroy(sll);
}

void CheckCountFind()
{
	sll_iterator iter1=0, iter2=0, iter3=0 , iter4=0 , it_check = 0 , iter_find=0;
	sll_t *sll= SLLCreate();
	char *string_find = "dani";
	char *string_not = "dummy";
	
	if(0 != SLLCount(sll))
	{
		printf("Count (1) Error\n");
	
	}
	
	iter1 = SLLInsert(SLLEnd(sll),"shir");
	iter2 = SLLInsert(SLLEnd(sll), "dani");
	iter3 = SLLInsert(SLLEnd(sll),"may");
	iter4 = SLLInsert(SLLEnd(sll), "miki");
	
	if(4 != SLLCount(sll))
	{
		printf("Count (2) Error\n");
	
	}
	
	it_check = SLLFind(iter1, iter4,string_find, TestMatchString);
	
	if (0 != strcmp(SLLGet(it_check), string_find))
    	{
        	printf("Find (1) Error\n");
   	 }

    	iter_find = SLLFind(iter2, iter4, string_not, TestMatchString);

    	if (0 != strcmp(SLLGet(iter_find), SLLGet(iter4)))
    	{
   	     printf("Find (2) Error\n");
    	}
    	(void)iter3;
	SLLDestroy(sll);
}
 
void CheckForeach()
{
	
	sll_iterator iter1=0, iter2=0, iter3=0 , iter4=0;
	int a = 2 , b=3 , c =4 ,d =5 , param =10;
	sll_t *sll= SLLCreate();

	
	iter1 = SLLInsert(SLLEnd(sll),&a);
	iter2 = SLLInsert(SLLEnd(sll),&b);
	iter3 = SLLInsert(SLLEnd(sll),&c);
	iter4 = SLLInsert(SLLEnd(sll),&d);
	
	SLLForEach(iter1, iter4, &param, TestAction);
	
	if(*((int*)SLLGet(iter1)) != 20)
	{
		printf("Foreach (1) Error");
	}
	if(*((int*)SLLGet(iter2)) != 30)
	{
		printf("Foreach (2) Error");
	}
	if(*((int*)SLLGet(iter3)) != 40)
	{
		printf("Foreach (3) Error");
	}
	if(*((int*)SLLGet(iter4)) == 50)
	{
		printf("Foreach (4) Error"); /*not includ 'to'*/
	}
	
	SLLDestroy(sll);

}
 


int TestMatchString(sll_iterator curr,void *param)
{
    return strcmp(SLLGet(curr), param);
}

int TestAction(sll_iterator curr,void *param)
{
	int *num = (int *)SLLGet(curr);
    	*num *= *(int *)param;
	
	return 0;
	
}

/*int main()
{
	test create*/
	/*int test;
	sll_t *my_slist = SLLCreate();
	sll_iterator iter_head = SLLBegin(my_slist);
	sll_iterator iter_tail = SLLEnd(my_slist);
	test = SLLIteratorsIsEqual(iter_head, iter_tail);
	printf("%d\n", test);
	SLLDestroy(my_slist);*/

	/*int test;
	int x = 3;
	sll_t *my_slist = SLLCreate();
	sll_iterator iter_head = SLLBegin(my_slist);
	sll_iterator iter_tail = SLLEnd(my_slist);
	sll_iterator iter_1 = SLLInsert(iter_tail, &x);
	iter_tail = SLLEnd(my_slist);
	test = SLLIteratorsIsEqual(iter_head, iter_tail);
	printf("%d\n", test);
	SLLDestroy(my_slist);
	return 0;
}*/





