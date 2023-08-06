/*********************************
 * Reviewer: 
 * Author: yisrael fisch       
 * File: sorted_list.c
 * ******************************/

#include <stdlib.h>/*malloc, free*/
#include <assert.h>/*assert*/
#include "sorted_list.h"




struct sorted_list
{
    dll_t *list;
    sorted_list_compare_func_t compare_func;
    void *user_param;
};


sorted_list_t *SortedListCreate(sorted_list_compare_func_t compare_func, void *user_param)
{
    sorted_list_t *solist = (sorted_list_t *)malloc(sizeof(sorted_list_t));
    assert(compare_func);
    
    if(!solist)
    {
        return NULL;
    }

    solist->list = DListCreate();
    if(!solist->list)
    {
        free(solist);
        solist = NULL;
        return NULL;
    }
    solist->compare_func = compare_func;
    solist->user_param = user_param;

    return solist;   
}

sorted_list_iterator_t SortedListIterInit(void)
{
    sorted_list_iterator_t iter;

    iter.iter = NULL;
    #ifndef NDEBUG
    iter.list = NULL;
    #endif
    return iter;
}

void SortedListDestroy(sorted_list_t *list)
{
    assert(list);
    DListDestroy(list->list);
    
    /*free(list->compare_func);*/
    list->compare_func = NULL;
    
    free(list);
    list = NULL;
}

size_t SortedListSize(const sorted_list_t *list)
{
    assert(list);
    return DListSize(list->list);
}

int SortedListIsEmpty(const sorted_list_t *list)
{
    assert(list);
    return DListIsEmpty(list->list);
}


sorted_list_iterator_t SortedListBegin(const sorted_list_t *list)
{
    sorted_list_iterator_t sort_iter;
    assert(list);
    
    sort_iter.iter = DListBegin(list->list);
    #ifndef NDEBUG
    sort_iter.list = (sorted_list_t*) list;
    #endif
    return sort_iter;

}

sorted_list_iterator_t SortedListEnd(const sorted_list_t *list)
{
    sorted_list_iterator_t sort_iter;
    assert(list);
    
    sort_iter.iter = DListEnd(list->list);
    #ifndef NDEBUG
    sort_iter.list = (sorted_list_t*)list;
    #endif
    return sort_iter;
}

sorted_list_iterator_t SortedListNext(sorted_list_iterator_t iter)
{
    iter.iter = DListNext(iter.iter);
    return iter;
}

sorted_list_iterator_t SortedListPrev(sorted_list_iterator_t iter)
{
    iter.iter = DListPrev(iter.iter);
    return iter;
}

int SortedListIsSameIter(sorted_list_iterator_t iter1, sorted_list_iterator_t iter2)
{
    #ifndef NDEBUG
    return (DListIsSameIter(iter1.iter, iter2.iter) && iter1.list == iter2.list);
    #else
    return DListIsSameIter(iter1.iter, iter2.iter);
    #endif
}

void *SortedListGetData(sorted_list_iterator_t iter)
{
    return DListGetData(iter.iter);
}

sorted_list_iterator_t SortedListInsert(sorted_list_t *list, void *data)
{
    sorted_list_iterator_t location = SortedListIterInit();
    sorted_list_iterator_t new_node = SortedListIterInit();
    assert(list);
    assert(data);

    location = SortedListFind(list, SortedListBegin(list), SortedListEnd(list), data);

    new_node.iter = DListInsert(list -> list, location.iter , data);

    return new_node;
}

void *SortedListPopFront(sorted_list_t *list)
{
    assert(list);
    return DListPopFront(list->list);
}

void *SortedListPopBack(sorted_list_t *list)
{
    assert(list);
    return DListPopFront(list->list);
}

sorted_list_iterator_t SortedListRemove(sorted_list_iterator_t curr)
{
    curr.iter = DListRemove(curr.iter);

    return curr;
}

int SortedListForEach
(sorted_list_iterator_t from, sorted_list_iterator_t to,
    void *param, sorted_list_action_func_t action_func)
{
    assert(from.list == to.list);
    assert(param);
    assert(action_func);
    return DListForEach(from.iter,to.iter,param,action_func);
   
}

void SortedListMerge(sorted_list_t *dest_list, sorted_list_t *src_list)
{
    sorted_list_iterator_t from = SortedListBegin(src_list);
    sorted_list_iterator_t to = SortedListBegin(src_list);
    sorted_list_iterator_t where = SortedListBegin(dest_list);

    assert(dest_list);
    assert(src_list);

    while(!SortedListIsEmpty(src_list))
    {
        from = to;
        where = SortedListFind(dest_list, where, SortedListEnd(dest_list), SortedListGetData(from));
        if(SortedListIsSameIter(where, SortedListEnd(dest_list)))
        {
            to = SortedListEnd(src_list);
        }
        else
        {
            to = SortedListFind(src_list, SortedListNext(from), SortedListEnd(src_list), SortedListGetData(where));
        }

        DListSplice(where.iter, from.iter, to.iter);
    }
}

sorted_list_iterator_t SortedListFind
(sorted_list_t *list, sorted_list_iterator_t from,
    sorted_list_iterator_t to, const void *data)
{
    assert(list);
    assert(data);

    while(!SortedListIsSameIter(from,to))
    {
        if(0 > list->compare_func(SortedListGetData(from), data, list->user_param))
        {
            return from;
        }
        
            from = SortedListNext(from);
    }

    return SortedListEnd(list);
}

sorted_list_iterator_t SortedListFindIf
(sorted_list_iterator_t from, sorted_list_iterator_t to,
    const void *data, sorted_list_is_match_func_t is_match_func)
{
    assert(from.list == to.list);
    assert(data);
    assert(is_match_func);
        
    from.iter = DListFind(from.iter, to.iter, data, is_match_func);

    return from;
}