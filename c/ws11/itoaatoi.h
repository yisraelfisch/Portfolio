/*************************************** 
file name: itoaatoi.h
Author: yisrael fisch
*reviewer: irit.
******************************************/
#ifndef __ITOAAOIT_H__
#define __ITOAAOIT_H__

#define ENDIAN (printf("%s\n", (char)1 ? "littel" : "big"))

int Atoi10(const char *nptr);

int Atoi(const char *nptr, int base);
/*you can send numbers and appercase letters depends on the base*/

char * Itoa(int n, char * buffer, int base);

void AtoiTest(char *str);

void LetterOnlyIn1and2Array(char *str1, char *str2, char *str3, int len1, int len2, int len3);

void Endian();



#endif /* __ITOAAOIT_H_ */