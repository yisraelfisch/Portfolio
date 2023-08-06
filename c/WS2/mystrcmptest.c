#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>

int Strcmp(const char *s1, const char *s2);

int main ()
{
	char one[] = "sarah";
	char two[] = "israel";
	int compare =  Strcmp(one ,two);

	printf("my result are %d\n", compare); 	
	
	printf("strcmp results %d\n", strcmp(one,two));  
      
return 0;
}







int Strcmp(const char *s1, const char *s2)

{
	int i = 0, result = 0;
	
	assert(s1);
	assert(s2);
	
	for (i = 0 ; '\0' != s1[i] || '\0' != s2[i]; i++)
	{
      if (s1[i] != s2[i])
      {
      	 result = (s1[i]) - s2[i];

      	 return result;
      }	
	}
	
	return result;
}