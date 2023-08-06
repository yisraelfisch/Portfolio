/*************************************** 
file name: wbo.h
Author: yisrael fisch
*reviewer: irit.
******************************************/
#ifndef __WBO_H__
#define __WBO_H__
#include <stddef.h>/*size_t*/

void *MemSet(void *s, int c, size_t n);

void *MeMcpy(void *dest, const void *src, size_t n);

void *MemMove(void *dest, const void *src, size_t n);


#endif /* __WBO_H_ */