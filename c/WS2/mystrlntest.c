#include <stdio.h>
#include <stddef.h>
#include <assert.h>
size_t Strlen(const char *s);

int main ()
{
	char test[] = "hello";
	int length =  Strlen(test);

	printf("length of string is: %d", length); 

return 0;
}


size_t Strlen(const char *s)
{
	int i;
    size_t counter = 0;
	
	assert(s);

	for (i = 0 ; '\0' != s[i]; i++)
	{
	counter++;
	}

	return counter;


}
