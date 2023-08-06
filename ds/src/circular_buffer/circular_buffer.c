/*********************************
 * Reviewer: nofar melamed
 * Author: yisrael fisch
 * File Name: circular_buffer.c
 * ******************************/

#include <stdlib.h> /*malloc, free*/
#include <stdio.h> /*printf*/
#include <stddef.h>/*offsetof*/
#include <assert.h>
#include "circular_buffer.h"



struct circular_buffer
{
	size_t head;
	size_t capacity;
	size_t in_use;
	char buffer[1];
};

circ_buff_t *CircBuffCreate(size_t capacity)
{
	circ_buff_t *c_buff;
	c_buff = malloc(offsetof(circ_buff_t ,buffer) + capacity);
	
	if (NULL == c_buff)
	{
		printf("circ_buff_t allocation failed \n");
		return NULL;
	}

	c_buff->head = 0;
	c_buff->capacity = capacity;
	c_buff->in_use = 0;
	/*c_buff->buffer = c_buff + 1; sizeof(circ_buff_t);*/

	return c_buff;

}

void CircBuffDestroy(circ_buff_t *c_buff)
{
	assert(c_buff);

	free(c_buff);
	c_buff = NULL;
}

size_t CircBuffFreeSpace(const circ_buff_t *c_buff)
{
	assert(c_buff);
	return (c_buff->capacity - c_buff->in_use);
}

size_t CircBuffBufSiz(const circ_buff_t *c_buff)
{
	assert(c_buff);

	return (c_buff->capacity);
}

int CircBuffIsEmpty(const circ_buff_t *c_buff)
{
    	assert(c_buff);
    	return (!(c_buff->in_use));
}

ssize_t CircBuffRead(circ_buff_t *c_buff, void *stream, size_t count)
{
	size_t i = 0;
	
	assert(c_buff);
	assert(stream);

	while( i < count && 0 != c_buff->in_use)
	{
		*((char *)stream + i) = *(c_buff->buffer + c_buff->head);

		c_buff->in_use -= 1;

		c_buff->head = (c_buff->head +1) % c_buff->capacity;
		
		++i;
	}

	return i;
}

ssize_t CircBuffWrite(circ_buff_t *c_buff, const void *stream, size_t count)
{
	size_t i = 0;

	assert(c_buff);
	assert(stream);

	while( i < count && c_buff->capacity != c_buff->in_use)
	{
		*((char *)c_buff->buffer + (c_buff->head + c_buff->in_use)
		 % c_buff->capacity) = *((char *)stream + i);

		c_buff->in_use += 1;

		++i;
	}

	return i;
}