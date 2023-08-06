/*************************************** 
file name: stack.c
Author: yisrael fisch
*reviewer: irit.
******************************************/
/*#include <stddef.h>size_t*/
#include <stdlib.h>/*malloc, free*/
#include <stdio.h>/*sizeof, size_t*/
#include <string.h>/*memcpy*/
#include <assert.h>

#include "stack.h"

struct stack
{
    char* stack;
    size_t element_size;
    size_t capacity;
    int size;
};

stack_t * StackCreate(size_t capacity, size_t  element_size)
{
    stack_t *stack_manage =(stack_t *)malloc(sizeof(stack_t));
    if(NULL == stack_manage)
    {
        return NULL;
    }

    stack_manage->stack =(char *)malloc(element_size*capacity);
    if(NULL == stack_manage->stack)
    {
        free(stack_manage);
        stack_manage = NULL;
        return NULL;
    }

    stack_manage->element_size = element_size;
    stack_manage->capacity = capacity;
    stack_manage->size = 0;

    return stack_manage; 
}

void StackPush(stack_t *stack_manage, void *element_to_push)
{
    assert(stack_manage);
    assert(element_to_push);
    memcpy(stack_manage->stack + stack_manage->size * stack_manage->element_size, element_to_push, stack_manage->element_size);
    ++stack_manage->size;
}

void StackPop(stack_t *stack_manage)
{
    assert(stack_manage);
    --stack_manage->size;
}

void StackPeek(stack_t*stack_manage, void *store_element)
{
    assert(stack_manage);
    memcpy(store_element, stack_manage->stack + (stack_manage->size -1) * stack_manage->element_size, stack_manage->element_size);
}

int StackIsEmpty(stack_t *stack_manage)
{
    assert(stack_manage);
    return(!stack_manage->size);
}

void StackDestroy(stack_t *stack_manage)
{
    assert(stack_manage);
    free(stack_manage->stack);
    stack_manage->stack = NULL;
    free(stack_manage);
    stack_manage = NULL;
}

size_t StackCapacity(stack_t *stack_manage)
{
    assert(stack_manage);
    return stack_manage->capacity;
}

size_t StackSize(struct stack *stack_manage)
{
    assert(stack_manage);
    return stack_manage->size;
}

void CheckInt()
{
    stack_t *s = StackCreate(3, sizeof(int));

    int x = 3;
    printf("*****\nint chek\n");
    printf("after creating %ld\n", StackSize(s));
    StackPush(s, &x);
    printf("after pushing %ld\n", StackSize(s));
    StackPop(s);
    printf("after poping %ld\n", StackSize(s));
    printf("capacity is %ld\n",StackCapacity(s));
    printf("empty check %d\n", StackIsEmpty(s));
    StackDestroy(s);
}

void CheckFloat()
{
    stack_t *s = StackCreate(3, sizeof(float));

    float x = 3;
    printf("*****\nfloat chek\n");
    printf("after creating %ld\n", StackSize(s));
    StackPush(s, &x);
    printf("after pushing %ld\n", StackSize(s));
    StackPop(s);
    printf("after poping %ld\n", StackSize(s));
    printf("capacity is %ld\n",StackCapacity(s));
    printf("empty check %d\n", StackIsEmpty(s));
    StackDestroy(s);
}