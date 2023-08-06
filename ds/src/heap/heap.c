/*********************************
 * Reviewer: 				
 * Author: Yisrael Fisch 			
 * File: heap.c					
 * ******************************/
 
 /**/

#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc & free*/

#include "heap.h"
#include "vector.h"
/*******Defines******/


/*******Structs******/
struct heap
{
    vector_t *vector;
    heap_is_less_func_t comp_func;
    void *user_param;
};

typedef struct node
{
    void *data;

}node_t;



/*******Service Funcs******/

static int ParentIndex(int curr_index);
static int LeftChildIndex(int curr_index);
static int RightChildIndex(int curr_index);
static int CompareChildren(heap_t *heap, int curr_index);
static int GetLastIndex(heap_t *heap);
static void Swap(void **data1, void **data2);
static void HeapifyUp(heap_t *heap, int curr_index);
static void HeapifyDown(heap_t *heap, int curr_index);
static void RemoveIndex(heap_t *heap, int index);
/*******Funcs Funcs******/
heap_t *HeapCreate(heap_is_less_func_t comp_ptr,void *user_param)
{
    heap_t *heap = NULL;

    heap = (heap_t *)malloc(sizeof(heap_t));
    if(!heap)
    {
        return NULL;
    }

    heap->vector = VectorCreate(1, sizeof(void *));
    if(!heap->vector)
    {
        free(heap);
        heap = NULL;
        return NULL;
    }

    heap->comp_func = comp_ptr;
    heap->user_param = user_param;

    return heap;
}

void HeapDestroy(heap_t *heap)
{
    VectorDestroy(heap->vector);
    
    heap->vector = NULL;
    heap->comp_func = NULL;
    heap->user_param = NULL;

    free(heap);
    heap = NULL;
}

size_t HeapSize(heap_t *heap)
{
    return (VectorSize(heap->vector));
}

int HeapIsEmpty(heap_t *heap)
{
    return (VectorIsEmpty(heap->vector));
}

void *HeapPeek(heap_t *heap)
{
    void **data =NULL;
    data = VectorGetAccess(heap->vector, 0);
    return *data; 
}

int HeapPush(heap_t *heap, const void *data)
{
    int last_index = 0;
    
    if(VectorPush(heap->vector, &data))
    {
        return 1;
    }
    
    last_index = GetLastIndex(heap);
    HeapifyUp(heap, last_index);

    return 0; 
}

void HeapPop(heap_t *heap)
{
    RemoveIndex(heap, 0);
    
}

void *HeapRemove(heap_t *heap,const void *data,heap_is_match_func_t is_match,void *user_param)
{
    int index = 0;
    void *found_data =NULL;
    (void *)user_param;
    
    for(index = 0 ; index <= GetLastIndex(heap); index++)
    {
        if(1 == is_match((*(void **)VectorGetAccess(heap->vector,index)),data, heap->user_param))
        {    
            found_data = (*(void **)VectorGetAccess(heap->vector, index));
        
             RemoveIndex(heap, index);
            return found_data;
        }        
    }   
   return found_data; 
}

static void RemoveIndex(heap_t *heap, int index)
{
    void **first_data = NULL;
    void **last_data = NULL;

    first_data = VectorGetAccess(heap->vector, index);
    last_data = VectorGetAccess(heap->vector, GetLastIndex(heap));

    Swap(first_data, last_data);
    VectorPop(heap->vector);

    if(HeapSize(heap) > 1)
    {
        HeapifyDown(heap, 0); 
    }
    
}

static void HeapifyUp(heap_t *heap, int curr_index)
{
        void **curr_data = VectorGetAccess(heap->vector, curr_index);
        void **parent_data = VectorGetAccess(heap->vector, ParentIndex(curr_index));

        if(curr_index > 0 && (!heap->comp_func(*parent_data, *curr_data, heap->user_param)))
        {
            Swap(parent_data, curr_data);
            curr_index = ParentIndex(curr_index);
            HeapifyUp(heap, curr_index);
        }
}

static int GetLastIndex(heap_t *heap)
{
    return (int)HeapSize(heap) -1;
}
static int LeftChildIndex(int curr_index)
{
    return (curr_index*2) + 1;
}
static int RightChildIndex(int curr_index)
{
    return (curr_index*2) + 2;
}

static int ParentIndex(int curr_index)
{
    return (curr_index-1)/2;
}
static int CompareChildren(heap_t *heap, int curr_index)
{
    void **left_child_data = VectorGetAccess(heap->vector, LeftChildIndex(curr_index));
    void **right_child_data = VectorGetAccess(heap->vector, RightChildIndex(curr_index));

    return (heap->comp_func(*left_child_data, *right_child_data, heap->user_param));

}

static void HeapifyDown(heap_t *heap, int curr_index)
{
    /*there is now children*/
    if(GetLastIndex(heap) <= curr_index*2)
    {
        return;
    }
    
    /*second child is smaller*/
    if(GetLastIndex(heap) >= RightChildIndex(curr_index) && /*0 >*/ !CompareChildren(heap,curr_index))
    {
        HeapifyUp(heap, RightChildIndex(curr_index));
        HeapifyDown(heap, RightChildIndex(curr_index));
    }
    else/*first child is smaller or no second child*/
    {
        HeapifyUp(heap, LeftChildIndex(curr_index));
        HeapifyDown(heap, LeftChildIndex(curr_index));
    }
        
}


static void Swap(void **data1, void **data2)
{
    void *temp = NULL;

    temp = *data1;
    *data1 = *data2;
    *data2 = temp; 

}


