#include <stdio.h>
#include "global.h"

int x = 1;
void PrintGlobalVariableAddress()
{
	printf("The adress is: %p\n", (void *)&x);
}