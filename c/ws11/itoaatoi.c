/*************************************** 
file name: itoaatoi.c
Author: yisrael fisch
*reviewer: irit.
******************************************/

#include <stddef.h>/*size_t*/
#include <stdlib.h>/*atoi*/
#include <stdio.h>/*printf*/
#include <ctype.h>/*toupper, isdigit, isspace*/
#include <assert.h>

#include "itoaatoi.h"



static size_t NumDigit(int n, int base);
/*give the number of digits acorrding to the base*/

static size_t NumDigit(int n, int base)
{
	size_t counter = 0;
	while(0 != n)
	{
		++counter;
		n /= base;
	}
	
	return counter;
}

int Atoi10(const char *nptr)
{
	
	int negative = 1;
	int result = 0;
	assert(nptr);

	while(isspace(*nptr))
	{
		++nptr;
	}

	if((*nptr) == '+' || ((*nptr) == '-'))
	{
		if((*nptr) == '-')
		{
			negative  = -1;
		} 
		++nptr;
	}
  
	while(*nptr && isdigit(*nptr))
	{ 
		result = (result * 10) + ((*nptr) - '0');
		
	    ++nptr;
	}
	return (result*negative);
}	

int Atoi(const char *nptr, int base)
{
	
	int negative = 1;
	int result = 0;
	assert(nptr);

	while(isspace(*nptr))
	{
		++nptr;
	}

	if((*nptr) == '+' || (*nptr) == '-')
	{
		if((*nptr) == '-')
		{
			negative = -1;
		} 
		++nptr;
	}
/*while(*nptr && (((*nptr) >= '0' && (*nptr) <= '9' && (*nptr) <= (base + '0' -1)) || (toupper(*nptr) >= 'A' && toupper(*nptr) < (base +'A'-10))))
*/	while((*nptr)) /*&& isdigit(*nptr) && (*nptr) <= (base + '0' -1)) || (toupper(*nptr) >= 'A' && toupper(*nptr) < (base +'A'-10)))*/
	{
	
		if(isdigit(*nptr) && (*nptr) <= (base + '0' -1)) 
		{
			result = (result * base) + ((*nptr) - '0');
		}
		else if((toupper(*nptr) >= 'A' && toupper(*nptr) < (base +'A'-10)))
		{	
			result = (result * base) + (toupper(*nptr) - ('A' - 10));
		}
		else
		{
			break;
		} 
		
	    ++nptr;
	}
	return (result*negative);
}

char * Itoa(int n, char *buffer, int base)
{
	
	size_t i = NumDigit(n, base) -1;
	assert(buffer);

	if(0 == n)
	{
		*buffer = '0';
	}
	if(n < 0)
	{
		*buffer = '-';
		n *= -1;
		++i;
	}

	while(n > 0)
	{
		if((n % base) <= 9)
		{
			*(buffer + i) = ((n % base) + '0');
		}
		else if((n % base) > 9)
		{
			*(buffer + i) = ((n % base) + ('A' -10));
		}
		n /= base;
		--i;
	}
	return buffer;
}

void AtoiTest(char *str)
{
	assert(str);
	printf("%d\n", atoi(str));
	printf("%d\n", Atoi10(str));
}

/*ex2*/
void LetterOnlyIn1and2Array(char *str1, char *str2, char *str3, int len1, int len2, int len3)
{
	
	int LUT_letter[128] = {0};
	int i = 0;
	assert(str1);
	assert(str2);
	assert(str3);

	 for(i = 0; i < len1; ++i)
	 {
	 	LUT_letter[(int)str1[i]] = 1;
	 }

	 for(i = 0; i < len2; ++i)
	 {
	 	if(LUT_letter[(int)str2[i]] == 1)
	 	{
	 		LUT_letter[(int)str2[i]] = 2;
	 	}
	 }
	 

	 for(i = 0; i < len3; ++i)
	 {
	 	if(LUT_letter[(int)str3[i]] == 2)
	 	{
	 		LUT_letter[(int)str3[i]] = 1;
	 	}
	 }

	 for(i = 0; i < 128; ++i)
	 {
	 	if(LUT_letter[i] == 2)
	 	{
	 		printf("%c\n",i);
	 	}
	 }
}
 
/*ex3*/

void Endian()
{
	printf("%s\n", (char)1 ? "littel" : "big");
}

