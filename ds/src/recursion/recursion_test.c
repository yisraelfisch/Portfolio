/*************************************** 
file name: recursion_test.c
Author: yisrael fisch
*reviewer: roy
******************************************/

#include <stdio.h>/*printf*/
#include <assert.h> /*assert*/
#include "recursion.h"
#include "stack.h"

void Fibonaccitest();
void StrLenTest();
void StrCmpTest();
void StrCpyTest();
void StrCatTest();
void StrStrStrTest();
void TestFlip();

int main ()
{
	Fibonaccitest();
	StrLenTest();
	StrCmpTest();
	StrCpyTest();
	StrCatTest();
	StrStrStrTest();
	TestFlip();
	return 0;
}

void Fibonaccitest()
{
	/*int one = 1;
	int five = 5;*/
	int nine = 9;
	printf("first element in FibonacciRecursively is: %d\n" ,FibonacciRecursively(nine));
	printf("first element in FibonacciIteratively is: %d\n" ,FibonacciIteratively(nine));
	
}

void StrLenTest()
{
	char arr[10] = "123456";
	printf("StrLen is: %lu\n", StrLen(arr));
}

void StrCmpTest()
{
	char arr1[10] = "123456";
	char arr2[10] = "123456";
	char arr3[10] = "123458";
	printf("StrCmp equal is: %d\n", StrCmp(arr1, arr2));
	printf("StrCmp not equal is: %d\n", StrCmp(arr1, arr3));
}

void StrCpyTest()
{
	char arr1[10] = "114";
	char arr3[10] = "111458";
	printf("StrCpy: %s\n", StrCpy(arr3, arr1));

}

void StrCatTest()
{
	char arr1[10] = " 123";
	char arr3[10] = "111458";
	printf("StrCat: %s\n", StrCat(arr3, arr1));

}

void StrStrStrTest()
{
	char arr1[10] = "114";
	char arr3[10] = "111458";
	printf("StrStr: %s\n", StrStr(arr3, arr1));

}

void TestFlip()
{
   node_t a , b ,c, d, ret;

   d.data =4;
   d.next = NULL;

   c.data = 3;
   c.next = &d;
   
   b.data = 2;
   b.next = &c;

   a.data = 1;
   a.next= &b;

   ret = a;
   
   assert(1 == (ret.data));
   assert (2 == (ret.next->data));
   assert(3 == (ret.next->next->data));
   assert(4 == (ret.next->next->next->data));
   assert(!ret.next->next->next->next);

   ret = *RecurFlipList(&a);

   assert(4 == (ret.data));
   assert(3 == (ret.next->data));
   assert(2 == (ret.next->next->data));
   assert(1 == (ret.next->next->next->data));
   assert(!ret.next->next->next->next);

}