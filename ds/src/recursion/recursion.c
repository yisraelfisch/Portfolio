/*************************************** 
file name: recursion.c
Author: yisrael fisch
*reviewer: roy
******************************************/

#include <string.h> /*strncmp, strln*/
#include <assert.h> /*assert*/
#include "recursion.h"
#include"stack.h"



int FibonacciRecursively(int element_index)
{
	if(element_index == 1)
	{
    	return 1;
	}
	else if(element_index == 0)
	{
    	return 0;
	}
	return FibonacciRecursively(element_index - 1)
		 + FibonacciRecursively(element_index - 2);
}

int FibonacciIteratively(int element_index)
{
	
		int a = 0, b = 1, c = 0, i = 2;

		if(element_index == 1)
		{
    		return 1;
		}
		else if(element_index == 0)
		{
    		return 0;
		}
			
		for (i = 2; i <= element_index; i++)
		{
				c = a + b;
				a = b;
				b = c;
		}
		return b;

}

size_t StrLen(const char *s)
{
	assert(s);

	if(!*s)
	{
		return 0;
	}

	return (1 + StrLen(++s));
}

int StrCmp(const char *s1, const char *s2)
{	
	assert(s1);
	assert(s1);

	
	if(*s1 != *s2 || !*s1)
	{
		return (*s1 - *s2);		
	}
	
    return (StrCmp(s1 + 1, s2 + 1)); 
}

char *StrCpy(char *dest, const char *src)
{ 
	assert(dest);
    assert(src);
    
    if(*src)
    {
    	*dest = *src;

    	(StrCpy(dest+1, src+1));
    }
    else
    {
    	*dest = '\0';

    }
    
    return dest;
}

 char *StrCat(char *dest, const char *src)
 { 	
 	
 	assert (dest);
    assert (src);
	if(*dest)
	{
		StrCat(dest + 1, src);
	}
	else
	{
		StrCpy(dest, src);
	}
	return (dest);
 	
 }

char *StrStr (const char *haystack, const char *needle)
{
	/*size_t needle_length = StrLen(needle);*/
	assert (haystack);
    assert (needle);

    if (!(strncmp(haystack, needle ,StrLen(needle))))
    {
    	return (char *)haystack;
    }
    else if(!*haystack)
    {
		return NULL;
	}
   return StrStr(haystack + 1, needle);	

}

node_t *RecurFlipList(node_t *head)
{
    node_t *new_head = NULL;

    assert(head);

    if (NULL == head->next)
    {
        return head;
    }

    new_head = RecurFlipList(head->next);

    head->next->next = head;
    head->next = NULL;

    return new_head;
}


/*void rcurpop(stack)
{
	if(notempty(stack))
	{
		x = pop(stack)
		rcurpop(stack)
		rcursort(stack, x)
	}
}

void rcursort(stack, x)
{
	if(empty(stack|| x > peak(stack)))
	{
		push(stack, x);
		return;

	}
	y = pop
	rcursort(stack, x)
	push(stack, y)

}*/

































