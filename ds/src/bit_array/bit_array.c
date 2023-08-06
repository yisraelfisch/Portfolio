/*********************************
 * Reviewer: avigail.m
 * Author: yisrael fisch       
 * File: bit_array.c
 * ******************************/
#include <assert.h>
#include <limits.h>/*CHAR_BIT*/
#include "bit_array.h"

bit_array_t BitArraySetAll(bit_array_t ba)
{
	return (ba | 0xffffffffffffffff);
}

bit_array_t BitArrayResetAll(bit_array_t ba)
{
	return (ba & 0x0);
}

bit_array_t BitArraySetOn(bit_array_t ba, size_t index)
{
	return (ba | (bit_array_t)1<<index);
}

bit_array_t BitArraySetOff(bit_array_t ba, size_t index)
{
	return (ba & ~((bit_array_t)1<<index));
}

bit_array_t BitArraySetBit(bit_array_t ba, char set, size_t index)
{
	ba &= ~((size_t)1 << index);
	
	return (ba | ((bit_array_t)set << index));
	/*return (set ? (ba | (bit_array_t)1<<index) : (ba & ~((bit_array_t)1<<index)));*/
}

bit_array_t BitArrayMirror(bit_array_t ba)
{
/* swap odd and even bits*/
ba = ((ba >> 1) & 0x5555555555555555) | ((ba & 0x5555555555555555) << 1);
/* swap consecutive pairs*/
ba = ((ba >> 2) & 0x3333333333333333) | ((ba & 0x3333333333333333) << 2);
/* swap nibbles*/
ba = ((ba >> 4) & 0x0F0F0F0F0F0F0F0F) | ((ba & 0x0F0F0F0F0F0F0F0F) << 4);
/* swap bytes*/
ba = ((ba >> 8) & 0x00FF00FF00FF00FF) | ((ba & 0x00FF00FF00FF00FF) << 8);
/* swap 2-byte long pairs*/
ba = ((ba >> 16) & 0x0000FFFF0000FFFF) | ((ba & 0x0000FFFF0000FFFF) << 16);
/* swap 4-byte long pairs*/
ba = ((ba >> 32) & 0x00000000FFFFFFFF) | ((ba & 0x00000000FFFFFFFF) << 32);
 return ba;
}

bit_array_t BitArrayRotateRight(bit_array_t ba, size_t num)
{
	return (ba >> num)|(ba << (sizeof(bit_array_t)*CHAR_BIT - num));
}

bit_array_t BitArrayRotateLeft(bit_array_t ba, size_t num)
{
	return (ba << num)|(ba >> (sizeof(bit_array_t)*CHAR_BIT - num));
}

bit_array_t BitArrayFlip(bit_array_t ba)
{
	return ~ba;
}

bit_array_t BitArrayFlipBit(bit_array_t ba, size_t index)
{
	return (ba ^ ((bit_array_t)1 << index));
}

size_t BitArrayCountOn(bit_array_t ba)
{
   size_t count = 0;
    while (ba) 
    {
        ba &= (ba - 1);
        count++;
    }
    return count;
}

size_t BitArrayCountOff(bit_array_t ba)
{
    size_t count = 0;
    while (ba) 
    {
        ba &= (ba - 1);
        count++;
    }
    return (sizeof(bit_array_t)*CHAR_BIT - count);	
}

size_t BitArrayGetVal(bit_array_t ba, size_t index)
{
	return (((ba & (bit_array_t)1 << index)) ? 1 : 0);
}

char *BitArrayToString(bit_array_t ba, char *str)
{
	int i = sizeof(bit_array_t)*CHAR_BIT - 1;
	assert(str);

	while(i >= 0)

	{
		*(str + i) = (ba % 2) + '0';
		ba /= 2;
		--i;
	}
	return str;
}











