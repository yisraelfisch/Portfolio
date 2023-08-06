#include <stdio.h>/*printf*/
#include "itoaatoi.h"

int main ()
{
 	char arr[10] = " 	-01;fg";

 	char arr1[8] = {0};

 	int y = 31;

 	char one[10] = "blabla?";
 	char two[10] = "israel?";
 	char three[10] = "bca";
	AtoiTest(arr);
 	printf("Atoi check is %d\n" , Atoi(arr,16));
 	Itoa(y, arr1, 16);
	printf("Iota check %s\n", arr1);
	ENDIAN;
	Endian();

	LetterOnlyIn1and2Array(one, two, three, 10, 10, 3);
 	return 0;
}