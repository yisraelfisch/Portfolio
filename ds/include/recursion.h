/*************************************** 
file name: recursion.h
Author: yisrael fisch
*reviewer: roy
******************************************/

#ifndef __RECURSION_H__
#define __RECURSION_H__

#include <stddef.h>/*size_t*/

typedef struct node
{
    int data;
    struct node *next;
} node_t;

int FibonacciRecursively(int element_index);
int FibonacciIteratively(int element_index);

size_t StrLen(const char *s);

int StrCmp(const char *s1, const char *s2);

char *StrCpy(char *dest, const char *src);

char *StrCat(char *dest, const char *src);

char *StrStr (const char *haystack, const char *needle);

node_t *RecurFlipList(node_t *head);

#endif /*__RECURSION_H__*/