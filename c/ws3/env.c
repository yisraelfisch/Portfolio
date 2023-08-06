/* A program to copy all the env* variables into a new char ** in lowaer
case and print them */
/* Author: yisrael fisch*/
/*reviewer: roy*/

#include <stdio.h> /*printf*/
#include <stdlib.h>/*malloc, free*/
#include <string.h>/*strlen*/
#include <ctype.h>/*tolower*/

int CountRows(char **src)/*function that count how many strings in envp*/
{
	int counter = 0;
	while(NULL != *(src + counter))
	{	
			++counter;
	}
	return counter;
}

/*function that change every chrachtar to lower case
copy the strings to dst,
print it and free the memory that was alllocate*/

void CopyLowerCaseToBuffer(char **dst, char **src)
{
	int i = 0;
	int j = 0;
	for(i = 0; NULL != src[i]; ++i)
		{
			for(j = 0; '\0' != src[i][j]; ++j)
			{

			dst[i][j] = tolower(src[i][j]);
			}
			dst[i][j] = '\0';
			printf("%s\n", dst[i]);
			free(dst[i]);

		} 
}

int main (int argc, char **argv, char **envp)
{
	int i = 0;
	
	char **dest;

	i = CountRows(envp); 

	dest = (char **)malloc(i * (sizeof(char*)));

	if(dest == NULL)
	{
 		printf("memory did not allocated");	
 		return -1;
	}

	
	i = 0;

	while(NULL != *(envp+i))
	{	
		dest[i] = (char *)malloc(strlen(envp[i])+1);

		if(dest[i] == NULL)
		{
 		printf("memory did not allocated");	
 		return -1;
		}
		++i;
	}

		CopyLowerCaseToBuffer(dest, envp);
		free(dest);


	return 0;

}