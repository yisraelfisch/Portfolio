/*********************************
 * Reviewer: nofar melamed
 * Author: yisrael fisch
 * File Name: circular_buffer_test.c
 * ******************************/

#include <stdio.h>/*printf, puts*/
#include "circular_buffer.h"

void CheckCreate();
void CheckFreeSpace();
void CheckBufsiz();
void CheckIsEmpty();
void CheckRead();
void CircBuffWriteRead_Test();

int main()
{
CheckCreate();
CheckFreeSpace();
CheckBufsiz();
CheckIsEmpty();
CheckRead();
CircBuffWriteRead_Test();

return 0;
}

void CheckCreate()
{
	circ_buff_t *check= CircBuffCreate(1024);
	printf("sizeof check is %lu\n" , sizeof(check));
	CircBuffDestroy(check);
}

void CheckFreeSpace()
{
	size_t capacity = 1024;
	circ_buff_t *check= CircBuffCreate(capacity);
	if(capacity == CircBuffFreeSpace(check))
	{
		printf("FreeSpace is working\n");
	}

	CircBuffDestroy(check);
}

void CheckBufsiz()
{
	size_t capacity = 1024;
	circ_buff_t *check= CircBuffCreate(capacity);
	if(capacity == CircBuffBufSiz(check))
	{
		printf("Bufsiz is working\n");
	}

	CircBuffDestroy(check);
}

void CheckIsEmpty()
{
	size_t capacity = 1024;
	circ_buff_t *check= CircBuffCreate(capacity);
	if(1 == CircBuffIsEmpty(check))
	{
		printf("BuffIsEmpty is working\n");
	}

	CircBuffDestroy(check);
}

void CheckRead()
{
 circ_buff_t *c_buff1 = CircBuffCreate(10);
    circ_buff_t *c_buff2 = CircBuffCreate(51);
    circ_buff_t *c_buff3 = CircBuffCreate(0);

    if(CircBuffBufSiz(c_buff1) != 10)
    {
        puts("Error: CircBuffBufSiz");
    }

    if(CircBuffBufSiz(c_buff2) != 51)
    {
        puts("Error: CircBuffBufSiz");
    }

    if(CircBuffBufSiz(c_buff3) != 0)
    {
        puts("Error: CircBuffBufSiz");
    }

    CircBuffDestroy(c_buff1);
    CircBuffDestroy(c_buff2);
    CircBuffDestroy(c_buff3);
}


void CircBuffWriteRead_Test()
{
    circ_buff_t *c_buff1 = CircBuffCreate(5);
    circ_buff_t *c_buff2 = CircBuffCreate(20);
    char stream1[6] = {'a', 'b', 'c', 'd', 'e', 'f'};
    char stream2[6] = {'\0'};
    char stream3[6] = {'\0'};
    char stream4[6] = {'\0'};
    int stream5[6] = {0, 1, 2, 3, 4, 5};
    int stream6[6] = {0};
    size_t i = 0;

    if(CircBuffWrite(c_buff1, stream1, 6) != 5)
    {
        puts("Error: CircBuffWriteRead");
    }

    if(CircBuffFreeSpace(c_buff1))
    {
        puts("Error: CircBuffWriteRead");
    }

    if(CircBuffRead(c_buff1, stream2, 6) != 5)
    {
        puts("Error: CircBuffWriteRead");
    }

    if(!CircBuffIsEmpty(c_buff1))
    {
        puts("Error: CircBuffWriteRead");
    }

    for(i = 0; i != 5; ++i)
    {
        if(stream2[i] != 'a' + (char)i)
        {
            puts("Error: CircBuffWriteRead");
        }
    }

    if(CircBuffWrite(c_buff1, stream1, 5) != 5)
    {
        puts("Error: CircBuffWriteRead");
    }

    if(CircBuffRead(c_buff1, stream3, 2) != 2)
    {
        puts("Error: CircBuffWriteRead");
    }

    if(CircBuffFreeSpace(c_buff1) != 2)
    {
        puts("Error: CircBuffWriteRead");
    }

    for(i = 0; i != 2; ++i)
    {
        if(stream3[i] != 'a' + (char)i)
        {
            puts("Error: CircBuffWriteRead");
        }
    }

    if(CircBuffWrite(c_buff1, stream1, 5) != 2)
    {
        puts("Error: CircBuffWriteRead");
    }

    if(CircBuffRead(c_buff1, stream4, 5) != 5)
    {
        puts("Error: CircBuffWriteRead");
    }

    for(i = 0; i != 3; ++i)
    {
        if(stream4[i] != 'c' + (char)i)
        {
            puts("Error: CircBuffWriteRead");
        }
    }

    if(CircBuffWrite(c_buff2, stream5, 20) != 20)
    {
        puts("Error: CircBuffWriteRead");
    }

    if(CircBuffRead(c_buff2, stream6, 20) != 20)
    {
        puts("Error: CircBuffWriteRead");
    }

    for(i = 0; i != 5; ++i)
    {
        if(stream6[i] != (int)i)
        {
            printf("%d\n%d\n", stream6[i], (int)i);
            puts("Error: CircBuffWriteRead3");
        }
    }

    CircBuffDestroy(c_buff1);
    CircBuffDestroy(c_buff2);
}



