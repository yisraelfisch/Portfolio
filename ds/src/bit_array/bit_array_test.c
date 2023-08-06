#include <stdio.h>
#include "bit_array.h"

int main()
{
	bit_array_t test = 21;
	bit_array_t test2 = 10;
	bit_array_t flip_bit;
	bit_array_t left_rot;
	bit_array_t right_rot;
	bit_array_t mirror;
	bit_array_t set_bit;
	bit_array_t set_off;
	bit_array_t set_on;
	bit_array_t reset_all;
	bit_array_t set_all;
	char check[64] = {0};
	char check1[64] = {0};
	char check2[64] = {0};
	char check3[64] = {0};
	char check4[64] = {0};
	char check5[64] = {0};
	char check6[64] = {0};
	char check7[64] = {0};
	char check8[65] = {0};
	char check9[65] = {0};
	

	*check = *BitArrayToString(test, check);
	printf("to string check: %s\n", check);
	printf("gat val check %lu\n", (BitArrayGetVal(test, 4)));
	printf("count off check %lu\n", (BitArrayCountOff(test)));
	printf("count on check %lu\n", (BitArrayCountOn(test)));
	flip_bit = BitArrayFlipBit(test, 63);
	printf("flip bit check %s\n", ((BitArrayToString(flip_bit, check9))));
	left_rot = BitArrayRotateLeft(test, 1);
	printf("rotate left check %s\n", (BitArrayToString(left_rot, check1)));
	right_rot = BitArrayRotateRight(test, 1);
	printf("rotate right check %s\n", (BitArrayToString(right_rot, check2)));
	mirror = BitArrayMirror(test);
	printf("mirror check %s\n", (BitArrayToString(mirror, check3)));
	set_bit = BitArraySetBit(test, 1, 1);
	printf("set bit check %s\n", (BitArrayToString(set_bit, check4)));
	set_off = BitArraySetOff(test, 4);
	printf("set off check %s\n", (BitArrayToString(set_off, check5)));
	set_on = BitArraySetOn(test,3);
	printf("set on check %s\n", (BitArrayToString(set_on, check6)));
	reset_all = BitArrayResetAll(test);
	printf("reset all check %s\n", (BitArrayToString(reset_all, check7)));
	set_all = BitArraySetAll(test2);
	printf("set all check %s\n", (BitArrayToString(set_all, check8)));
	
	return 0;

}

/*6148914691236517205*/