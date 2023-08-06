/*********************************
 * Reviewer: roy mantel
 * Author: yisrael fisch       
 * File: dll.c
 * ******************************/

#include <stdlib.h>/*malloc, free*/
#include <assert.h> /*assert*/
#include "dll.h"

struct dll 
{
    dll_iterator_t head;
    dll_iterator_t tail;
};

struct dll_node
{
    void *data;
    dll_iterator_t next;
    dll_iterator_t prev;
};

dll_t *DListCreate(void)
{
    dll_t *dll = (dll_t *)malloc(sizeof(dll_t));
    if(!dll)
    {
        return NULL;
    }

    dll->head = (dll_iterator_t)malloc(sizeof(struct dll_node));
    if(!dll->head)
    {
        free(dll);
        dll = NULL;
        return NULL;
    }

    dll->tail = (dll_iterator_t)malloc(sizeof(struct dll_node));
    if(!dll->tail)
    {
        free(dll->head);
        free(dll);
        dll->head = NULL;
        dll = NULL;
        return NULL;
    }

    dll->head->data = dll->tail->data = dll;
    dll->head->prev = dll->tail->next = NULL;
    dll->head->next = dll->tail;
    dll->tail->prev = dll->head;

    return dll;
}

void DListDestroy(dll_t *dlist)
{
    dll_iterator_t curr = dlist->head;
    dll_iterator_t temp = curr;
    assert(dlist);
    
    while(NULL != curr->next)
    {
        curr = curr->next;
        free(temp);
        temp = curr;
    }
    free(curr);
    curr = NULL;
    free(dlist);
    dlist = NULL;
}

size_t DListSize(const dll_t * dlist)
{
    size_t counter = 0;
    dll_iterator_t temp = DListBegin(dlist);
    
    assert(dlist);
    
    
    while(NULL != temp->next)
    {
        ++counter;
        temp = temp->next;
            
    }
    return counter;
}

int DListIsEmpty(const dll_t *dlist)
{
    assert(dlist);
    return (DListIsSameIter(DListBegin(dlist), DListEnd(dlist)));
}

dll_iterator_t DListBegin(const dll_t *dlist)
{
    assert(dlist);
    return DListNext(dlist->head);
}

dll_iterator_t DListEnd(const dll_t *dlist)
{
    assert(dlist);
    return dlist->tail;
}

dll_iterator_t DListNext(const dll_iterator_t curr)
{
    assert(curr);
    return curr->next;
}

dll_iterator_t DListPrev(const dll_iterator_t curr)
{
    assert(curr);
    return curr->prev;   
}

int DListIsSameIter(dll_iterator_t first, dll_iterator_t second)
{
    assert(first);
    assert(second);

    return first == second;
}

void* DListGetData(dll_iterator_t curr)
{
    assert(curr);
    return (curr->data);
}

dll_iterator_t DListPushFront(dll_t *dlist, void *data)
{
    assert(dlist);
    assert(data);
    return DListInsert(dlist, DListBegin(dlist), data);
}

dll_iterator_t DListPushBack(dll_t *dlist, void *data)
{
    assert(dlist);
    assert(data);
    return DListInsert(dlist, DListEnd(dlist), data);
}

void *DListPopFront(dll_t *dlist)
{
    void *temp = 0;
    assert(dlist);
    temp = DListGetData(DListBegin(dlist));

    DListRemove(DListBegin(dlist));

    return temp;
}

void *DListPopBack(dll_t *dlist)
{
    void *temp = 0;
    assert(dlist);
    temp = DListGetData(DListPrev(DListEnd(dlist)));

    DListRemove(DListPrev(DListEnd(dlist)));

    return temp;   
}

dll_iterator_t  DListInsert(dll_t *dlist, dll_iterator_t curr, void *data)
{
    dll_iterator_t new_node = (dll_iterator_t)malloc(sizeof(struct dll_node));
    assert(dlist);
    assert(curr);
    assert(data);

    if (NULL == new_node)
    {
        return dlist->tail; 
    }
    
    new_node->data = data; 
    new_node->next = curr;
    new_node->prev = curr->prev;
    curr->prev->next = new_node;
    curr->prev = new_node;

    return new_node;
}

dll_iterator_t DListRemove(dll_iterator_t curr)
{
    dll_iterator_t temp = curr->next;
    assert(curr);

    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    free(curr);
    curr = NULL;

    return temp;
}

dll_iterator_t DListSplice
(dll_iterator_t where, dll_iterator_t begin, dll_iterator_t end)
{
    dll_iterator_t where_prev = DListPrev(where);
    dll_iterator_t begin_prev =  DListPrev(begin);
    dll_iterator_t end_prev = DListPrev(end);

    assert(where);
    assert(begin);
    assert(end);
    
    begin_prev->next = end;
    end->prev = begin_prev;

    begin->prev = where_prev;
    where_prev->next = begin;

    where->prev = end_prev;
    end_prev->next = where;

    return where_prev;
} 

int DListForEach
(dll_iterator_t from, dll_iterator_t to,
 void *param, action_func_t func)
 {
    

    assert(from);
    assert(to);
    assert(param);
    assert(func);

    while(!DListIsSameIter(from, to))
    {
        if(func(from->data, param))
        {
            return 1;
        }

        from = from->next;
    }

    return 0;
 }

 dll_iterator_t DListFind
(dll_iterator_t from, dll_iterator_t to,
 const void *data, is_match_t func)
{
    assert(from);
    assert(to);
    assert(data);
    assert(func);

    while(!DListIsSameIter(from, to) && func(from->data, data))
    {  

        from = from->next;
    }

    return from;
}

int DListMultiFind
(dll_iterator_t from, dll_iterator_t to, dll_t *dlist_dest,
 const void *data, is_match_t func)
 {
    int counter = 1;

    assert(from);
    assert(to);
    assert(dlist_dest);
    assert(data);
    assert(func);

    while(!DListIsSameIter(from, to))
    {
        if(func(from->data, data))
        {
            DListPushBack(dlist_dest, from->data);
            
            counter = 0;    
        }

        from = from->next;
    }

    return counter;
 }


