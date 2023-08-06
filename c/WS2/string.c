#include <stddef.h>
#include <ctype.h>    /*tolower*/
#include <assert.h>
#include <stdlib.h> /*memory allocation */
#include "string.h" /* Why is it like this? */


size_t StrLen(const char *s)
{
    size_t counter = 0;
	
	assert(s);

	while ('\0' != *s)
	{
	++s;	
	++counter;
	}

	return counter;
}

int StrCmp(const char *s1, const char *s2)

{	
	assert(s1);
	assert(s1);

	while ('\0' != *s1 && *s1 == *s2)
	{
      	++s1;
        ++s2;
	}

    return (*s1 - *s2); 
}

char *StrCpy(char *dest, const char *src)
{ 
	char *start = dest;
	assert(dest);
    assert(src);

    while('\0' != *src)
    {
        *dest = *src;
        ++dest;
        ++src;
    }

    *dest = '\0';

    return start;
}

char *StrnCpy(char *dest, const char *src, size_t n)
{ 

	char *dest_start = dest;
    assert(dest);
    assert(src);

    while(0 < n && *src != '\0')
    {
        
        *dest++ = *src++;
        --n;
    }

    while (0 != n)
    {
    	*dest++ = '\0';
    	--n;
    }
    return (dest_start);

}

int StrnCmp(const char *s1, const char *s2, size_t n)

{
	assert(s1);
	assert(s2);

	while ('\0' != *s1 && *s1 == *s2 && (n - 1) > 0)
	{
      	++s1;
        ++s2;
        --n;
	}

    return (*s1 - *s2); 
}

int StrCaseCmp(const char *s1, const char *s2)
{
	int i = 0, result = 0;
	
	assert(s1);
	assert(s2);
	while ('\0' != *s1 && tolower(*s1) == tolower(*s2))
	{
      ++s1;
      ++s2;
	}
	
	return tolower(*s1) - tolower(*s2)
	
} 

char *StrChr(const char *s, int c)
{
    char *counter = (char*)s;

	assert(s);

	while('\0' == *counter && *counter != c)
	{
		++counter;
	}
	
    return (*counter == c ? counter : NULL);
		
		 
}
 
 char *StrDup(const char *s)
 {
    size_t n = StrLen(s)+1;
	char *new_s = NULL;

	assert (s);

	new_s = ((char*)malloc (n * sizeof(char));
    if(NULL == new_s)
    {
    	return NULL;
    }
	return StrCpy(new_s,(char*)s));

 }

 char *StrCat(char *dest, const char *src)
 {
 	char *dest_end = dest + StrLen(dest);
 	assert (dest);
    assert (src);
 	StrCpy(dest_end, src);
     
     return dest;
 }

 char *StrnCat(char *dest, const char *src, size_t n)
{
    char *dest_end = dest + StrLen(dest);

 	assert (dest);
    assert (src);

 	StrnCpy(dest_end, src, n);
     
     
    return dest;

}

char *StrStr (const char *haystack, const char *needle)
{
	size_t needle_length = StrLen(needle);
	assert (haystack);
    assert (needle);

	while ('\0' != *haystack)
	{
		if (0 == StrnCmp(haystack, needle ,needle_length))
		{
			return (char*)haystack;
		}
		haystack++;
	}

	return NULL;

}
 size_t StrSpn(const char *s, const char *accept)
 {
	 size_t counter = 0;

	 assert(s);
	 assert(accept);

	 while (*s !='\0' && Strchr(accept, *s))
     {
      counter ++;
      s++;
     }

     return counter;

 }

 int IsPalindrome(char *str)
{
   
    size_t i = 0;
    size_t n = StrLen(str) - 1;
    assert(str);
 
    while (n > i)
    {
        if (*(str+i) != (*(str +n)))
        {
            return 0;
            
        }
        i++;
        n--;
    }
    return 1;

}

   
