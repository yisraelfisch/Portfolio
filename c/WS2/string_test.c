#include "string.h" 
#include <stdio.h> /*for tests*/
#include <string.h> /*for tests*/

int main(int argc, char *argv[])
{
        char test[] = "hello";    
	int length =  StrLen(test);
	size_t n =3;
        char *dup = NULL;
        char one[] = "SARAH";
        char one1[] = "SARAH";
        char two1[] = "ysrae";
	char two[] = "SARael";
	char three [] = "iSRAEL";
	char str[30] = "sarah";
	char str1[30]= "sarah";
	char str2[30]= "sarah";
	char str3[30]= "sarah";
	char str4[30]= "cd";
	char str5[30]= "abcdef";
	char str6[]= "abcdef";
	char str7[]= "aby";
	char palindrom[] = "ab  ba";
	int n1 = 3;
	int compare =  StrCmp(one ,two);
        size_t spn = StrSpn(str7 ,str6);
        dup = StrDup(test);
	
	/*printf("length of string is: %d\n", length); 

	printf("my result are %d\n", compare); 	
	
	printf("strcmp results %d\n", StrCmp(one,two));*/

	printf("result of Strncmp %d\n", StrnCmp(two, one, n1));   

	/*printf(" before Strcpy results %s\n", two); 

	printf("Strcpy results %s\n", StrCpy(two1, one1));

	printf("my Strncpy results %s\n", StrnCpy(two, one, n1));
	printf("Strncpy results %s\n", strncpy(two, one, n1));


	printf("strCasecmp results %d\n", StrCaseCmp(three,two));

	printf("Strchr result %p\n", strchr(one,'S'));
        printf("strchr result %p\n", StrChr(one,'S'));

        printf("Strdup results %s\n", dup); 
        free(dup);

        printf("Strcat results %s\n", StrCat(str1, str));
        printf("StrnCat results %s\n", StrnCat(str2, str3,n));

        printf("StrStr result  %p %p\n", (str5 + 2), StrStr(str5,str4));
	
 	printf("Strspn results %lu\n", spn);

	printf("Strspn results %lu\n", StrSpn(str7,str6));

	printf("ispalindrom result %d", IsPalindrome(palindrom));*/
    return 0;
}

/* Why is it like this? */
