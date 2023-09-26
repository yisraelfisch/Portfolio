/*************************************** 
file name: bitwise.c
Author: yisrael fisch
*reviewer: yakov.
******************************************/
#include "bitwise.h"
#include <stdio.h>

long Pow2(unsigned int x, unsigned int y)
{
	return  x << y;
}

int IsPow2(unsigned int n)
{
return (n & (n - 1))? 0: 1;

}

int IsPow2Loop(unsigned int n)
{
	int counter = 0;
	while(0 != n)
	{
		if((n & 1) == 1)
		{
			++counter;
		}
		n = n >> 1;
	}
 
 return (counter==1 ? 1 : 0);
}

int AddOne(int x)
{
	int m = 1;
	
	while(x & m)
	{
		x = x ^ m;
		m <<=1;
	}
	x = x ^ m;
	
	return x;
   /*return (-(~x))*/;
}

void ReturnThreeBitesOnOnly(unsigned int *arr , int n)
{
	int i = 0;
	for(i = 0; i < n; ++i)
	{
		int count = 0;
		int temp = *(arr+i);
		while(0 != temp)
		{
			if(1 == (temp &1))
			{
				++count;
			}
			temp = temp >> 1;
		}
		if(3 == count)
		{
			printf(" the number %u has three bytes on", (*(arr+i)));
		}
	}
}

 char LoopByteMiror(char n)
{
	int i;
	 char reverse_num = 0;
	for (i = 0; i < 8; i++) 
	{
        reverse_num = (reverse_num << 1)| (n & 1);
        n = n >> 1;
       
    }
    return reverse_num;

}

char ByteMiror(char n)
{
   n = (n & 0xF0) >> 4 | (n & 0x0F) << 4;
   n = (n & 0xCC) >> 2 | (n & 0x33) << 2;
   n = (n & 0xAA) >> 1 | (n & 0x55) << 1;
   return n;
}


unsigned char Byte2ndAnd6thOn(unsigned char n)
{
return((n & 32) && (n & 2));
}

unsigned char Byte2ndOr6thOn(unsigned char n)
{
return((n & 32) || (n & 2));
}

unsigned char Swap3rdAnd5thByte(unsigned char n)
{
	unsigned char result = 0;
    unsigned char bit3 =  (n >> 2) & 1;
    unsigned char bit5 =  (n >> 4) & 1;
    unsigned char x = (bit3 ^ bit5);
 
    x = (x << 2) | (x << 4);
 
    return result = n ^ x;

}

unsigned int ClosestNumDivisibleBy16(unsigned int n)
{
	
	return (n = n & 0xfffffff0);	
}

void SwapWithXor(int *xp, int *yp)
{
   *xp = *xp ^ *yp;
   *yp = *xp ^ *yp;
   *xp = *xp ^ *yp;
}

int CountSetBits(int n)
{
    int count = 0;
    while (0 != n)
    {
        count += n & 1;
        n >>= 1;
   }
    return count;
}

int CountSetBitsLut(int n)
{
	int set_of_4bits[16] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4 };

    return (set_of_4bits[n & 0xf] +
            set_of_4bits[(n >> 4) & 0xf] +
            set_of_4bits[(n >> 8) & 0xf] +
            set_of_4bits[(n >> 12) & 0xf] + 
            set_of_4bits[(n >> 16)& 0xf] +
            set_of_4bits[(n >> 20) & 0xf] +
            set_of_4bits[(n >> 24) & 0xf] +
            set_of_4bits[(n >> 28) & 0xf]);
}

void PrintFloatBin(float n)
{
  int *num = (int *)& n;

  int i = 31;
  printf("the binary representation is: ");
    	while (0 != i)
    	{
        printf("%d", ((*num  >> i) & 1));
        --i;
    	}
}
