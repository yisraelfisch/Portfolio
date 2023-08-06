/*************************************** 
file name: wbo.c
Author: yisrael fisch
*reviewer: irit.
******************************************/

#include "wbo.h"

/*check if adress is word aligned end return the ofset */
static int IsWordAaligned(void *s);

/*set a long word string with the c value*/
static size_t SetWord(int c);

static int IsWordAaligned(void *s)
{
	return ((long)s % sizeof(size_t));
}


static size_t SetWord(int c)
{
	size_t word = 0;
	int i = sizeof(size_t);
	while(i > 0)
	{
		word<<= sizeof(size_t);
		word ^= c;
		
		--i; 
	}
	return word;
}

void *MemSet(void *s, int c, size_t n)
{
	assert(s);
 	char *dest = (char *)s;
 	int runner = IsWordAaligned(s);
	size_t word = SetWord(c);

	while(runner > 0 && n > 0)
	{
		*dest = (char)c;
		--runner;
		--n;
		++dest;
	}

	while(n >= sizeof(size_t))
	{
		*(size_t *)dest = word;
		n = n - sizeof(size_t);
		dest += sizeof(size_t);
	
	}
	
	while (n > 0)
	{
		*dest = (char)c;
		--n;
		++dest;
	
	}
	return s;
}

void *MeMcpy(void *dest, const void *src, size_t n)
{
	assert(src);
	assert(dest);
	char *s = (char *)src;
	char *d = (char *)dest;
 	int runner = IsWordAaligned(dest);

	while(runner > 0 && n > 0)
	{
		*d = *s;
		--runner;
		--n;
		++d;
		++s;
	}

	while(n >= sizeof(size_t))
	{
		*(size_t *)d = *(size_t *)s;
		n = n - sizeof(size_t);
		d += sizeof(size_t);
		s += sizeof(size_t);
	}
	while (n > 0)
	{
		*d = *s;
		--n;
		++d;
		++s;
	}
	
	return dest;
}

void *MemMove(void *dest, const void *src, size_t n)
{
	assert(dest);
	assert(src);
	char *s = (char *)src + n;
	char *d = (char *)dest + n;

	if((char *)dest <= s && dest >= src)
	{
		int runner = IsWordAaligned(d);
		/*s = s + n - 1;
		d = d + n - 1;*/
 		

		while(runner > 0 && n > 0)
		{
			--d;
			--s;
			*d = *s;
			--runner;
			--n;
			
		}

		while(n >= sizeof(size_t))
		{
			d -= sizeof(size_t);
			s -= sizeof(size_t);
			*(size_t *)d = *(size_t *)s;
			n = n - sizeof(size_t);
		}

		while (n > 0)
		{
			--d;
			--s;
			*d = *s;
			--n;
			
		}	
	}
	else
	{
		MeMcpy(dest, src, n);
	}

	return dest;

}

