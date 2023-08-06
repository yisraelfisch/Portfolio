/*************************************** 
file name: b_test.c
Author: yisrael fisch
*reviewer: yakov.
******************************************/
#include "bitwise.h"
#include <stdio.h>

int main()
{
	long int x = 7;
	long int n = 2;
 	int y = 89566;
 	unsigned int arr4[6]={23, 63743, 634623, 84,7, 19};
 	char r = (-128);
 	unsigned char z = 15;
 	unsigned int n16 = 1624;
 	int a = 7;
 	int b = 10;
 	int *pa = &a;
 	int *pb = &b; 
	int countbits = 2147483647;
	float f = 10.1;

	printf("Pow2 is: %ld\n", Pow2(x,n));
	printf("IsPow2 is: %d\n%d\n", IsPow2(n),IsPow2(x));
	printf("IsPow2Loop: %d\n%d\n", IsPow2Loop(n),IsPow2Loop(x));
	printf("AddOne: %d\n", AddOne(y));
    ReturnThreeBitesOnOnly(arr4, 6);
    printf("\nLoopByteMiror is: %d\n", LoopByteMiror(r));
    printf("\nByteMiror is: %d\n", ByteMiror(r));
    printf("\nByte2ndAnd6thOn is: %d\n",Byte2ndAnd6thOn(z));
    printf("\nByte2ndOr6thOn is: %d\n",Byte2ndOr6thOn(z));
	printf("\nSwap3rdAnd5thByte is: %d\n",Swap3rdAnd5thByte(z));
	printf("\nClosestNumDivisibleBy16 is: %d\n",ClosestNumDivisibleBy16(n16));
	printf("\nbefore swap a is: %d b is: %d\n",a ,b);
	SwapWithXor(pa, pb);
	printf("\nafter swap a is: %d b is: %d\n",a ,b);
	printf("\nCountSetBits is: %d\n", (CountSetBits(countbits)));
	printf("\nCountSetBitsLut is: %d\n", (CountSetBitsLut(countbits)));
	PrintFloatBin(f);
	return 0;
}	