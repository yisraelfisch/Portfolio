#ifndef __STRING_H__
#define __STRING_H__
#include <stddef.h> /* size-t*/
#include <assert.h> /* assert*/
#include <stdlib.h>

/* Why is it like this? */

size_t StrLen(const char *s);

int StrCmp(const char *s1, const char *s2);

char *StrCpy(char *dest, const char *src);

char *StrnCpy(char *dest, const char *src, size_t n);

int StrnCmp(const char *s1, const char *s2, size_t n);

int StrCaseCmp(const char *s1, const char *s2);

char *StrChr(const char *s, int c);

char *StrDup(const char *s);

char *StrCat(char *dest, const char *src);

char *StrnCat(char *dest, const char *src, size_t n);

char *StrStr(const char *haystack, const char *needle);

size_t StrSpn(const char *s, const char *accept);

int IsPalindrome(char *str);



#endif /* __STRING_H__ */
