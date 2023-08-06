/*************************************** 
file name: bitwise.h
Author: yisrael fisch
*reviewer: yakov.
******************************************/
#ifndef __BITWISE_H__
#define __BITWISE_H__

long Pow2(unsigned int x, unsigned int y);

int IsPow2(unsigned int n);

int IsPow2Loop(unsigned int n);

int AddOne(int x);

void ReturnThreeBitesOnOnly(unsigned int *arr , int n);

char LoopByteMiror( char n);

char ByteMiror(char n);

unsigned char Byte2ndAnd6thOn(unsigned char n);

unsigned char Byte2ndOr6thOn(unsigned char n);

unsigned char Swap3rdAnd5thByte(unsigned char n);

unsigned int ClosestNumDivisibleBy16(unsigned int n);

void SwapWithXor(int *xp, int *yp);

int CountSetBits(int n);

int CountSetBitsLut(int n);

void PrintFloatBin(float n);

#endif /* __BITWISE_H_ */