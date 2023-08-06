/*************************************** 
file name: vector.c
Author: yisrael fisch
*reviewer: .
******************************************/
/*#include <stddef.h>size_t*/
#include <stdlib.h>/*malloc,realloc, free*/
#include <stdio.h>/*sizeof, size_t*/
#include <string.h>/*memcpy*/
#include <assert.h>
#include "vector.h"
enum err {SUCCESS, ALLOC_FAILED};

struct vector
{
    char* vector;
    size_t element_size;
    size_t capacity;
    size_t size;
};

/*function that resize the vector according to the capacity needed*/
static vector_t *Resize(vector_t *vector_manage, size_t capacity);


vector_t *VectorCreate(size_t capacity, size_t element_size)
{
    vector_t *vector_manage =(vector_t *)malloc(sizeof(vector_t));
    if(NULL == vector_manage)
    {
        return NULL;
    }

    vector_manage->vector =(char *)malloc(element_size*capacity);
    if(NULL == vector_manage->vector)
    {
        free(vector_manage);
        vector_manage = NULL;
        return NULL;
    }

    vector_manage->element_size = element_size;
    vector_manage->capacity = capacity;
    vector_manage->size = 0;

    return vector_manage; 
}

static vector_t *Resize(vector_t *vector_manage, size_t capacity)
{
    vector_manage->vector =(char *)realloc(vector_manage->vector, vector_manage->element_size*capacity);
    if(NULL == vector_manage->vector)
    {
        free(vector_manage);
        vector_manage = NULL;
        return NULL;
    }
    return vector_manage;
}

void VectorDestroy(vector_t *vector_manage)
{
    assert(vector_manage);
    free(vector_manage->vector);
    vector_manage->vector = NULL;
    free(vector_manage);
    vector_manage = NULL;
}

int VectorPush(vector_t *vector_manage, void *element_to_push)
{
    assert(vector_manage);
    assert(element_to_push);
    if(vector_manage->capacity == vector_manage->size)
    {
        if(!(vector_manage = Resize(vector_manage, (vector_manage->capacity*2))))
        {
            return ALLOC_FAILED;
        }
        vector_manage->capacity *= 2;
    }
    memcpy(vector_manage->vector + vector_manage->size * vector_manage->element_size, element_to_push, vector_manage->element_size);
    ++vector_manage->size;

    return SUCCESS;
}

void VectorPop(vector_t *vector_manage)
{
    assert(vector_manage);
    --vector_manage->size;
}

int VectorIsEmpty(vector_t *vector_manage)
{
    assert(vector_manage);
    return(vector_manage->size == 0);
}

size_t VectorSize(vector_t *vector_manage)
{
    assert(vector_manage);
    return vector_manage->size;
}

size_t VectorCapacity(vector_t *vector_manage)
{
    assert(vector_manage);
    return vector_manage->capacity;
}

void *VectorGetAccess(vector_t *vector_manage, int index)
{
    assert(vector_manage);
    return (vector_manage->vector + (index*vector_manage->element_size));
}

int VectorShrinkToFit(vector_t *vector_manage)
{
    assert(vector_manage);
    if(!(vector_manage = Resize(vector_manage, vector_manage->size)))
    {
            return ALLOC_FAILED;
    }

    vector_manage->capacity = vector_manage->size;
    
    return SUCCESS;
}

int VectorReserve(vector_t *vector_manage, size_t new_capacity)
{
    assert(vector_manage);
    if(!(vector_manage = Resize(vector_manage, new_capacity )))
    {
        return ALLOC_FAILED;
    }

    vector_manage->capacity = new_capacity;
    
    return SUCCESS;   
}



