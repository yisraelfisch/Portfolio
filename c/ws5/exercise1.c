/*************************************** 
file name: exercise1.c
Author: yisrael fisch
*reviewer: daniel.b.
******************************************/
#include <stdio.h> /*printf*/

typedef void (*fp)(int);

typedef struct
{
	int num;
	fp pprint;
}print_me;

void Print(int x)
{
	printf("%d\n", x);
}

int main ()
{

	print_me arr[10];
	int i;
	for(i = 0; i < 10; ++i)
	{
		arr[i].num = i;
		arr[i].pprint = Print;
		arr[i].pprint(arr[i].num);
	}



return 0;
}