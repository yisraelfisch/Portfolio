/*********************************
 * Reviewer: 
 * Author: 
 * File Name: merge_quick.c
 * ******************************/

#include <stdlib.h>/*malloc, free*/
#include <string.h> /*memcpy*/
#include <assert.h>
#include "merge_quick.h"

static void RecurMergeSort(void *arr_to_sort, void *temp_arr,
                        size_t num_elements, size_t elem_size,
            int(*is_before)(const void *elem1, const void *elem2));

static void MergeHalves(void *left_start, void *right_start,
            void *temp_arr, size_t num_elements, size_t elem_size,
            int(*is_before)(const void *elem1, const void *elem2));

static void RecurQuickSort(void *arr_to_sort, void *temp_swap,
                        size_t num_elements, size_t elem_size,
                      int(*is_before)(const void *elem1, const void *elem2));

static size_t QuickPartition(void *arr_to_sort, void *temp_swap
                        , size_t num_elements, size_t elem_size,
                    int(*is_before)(const void *elem1, const void *elem2));

static void Swap(void *elem1, void *elem2, void *temp_swap, size_t elem_size);

int IterBinarySearch(int *array, size_t arr_size ,int data_to_find)
{
    int mid = 0;
    int low = 0;
    int high = 0;

    assert(array);

    high = arr_size - 1;
    while(low <= high)
    {
        /*find the mid between low and high index*/
        mid = low + (high - low)/2;

        if(array[mid] == data_to_find)
        {
            return mid;
        }

        if(array[mid] < data_to_find)
        {
            low = mid + 1;
        }
        else
        {
            high = mid -1;
        }

    }

    return -1;
}

int RecurBinarySearch(int *array, size_t arr_size ,int data_to_find)
{
    int mid = 0;
    int low = 0;
    int high = 0;
    int res = 0;
    

    assert(array);

    high = arr_size - 1;

    if(low <= high)
    {
        /*find the mid between low and high index*/
        mid = low + (high - low)/2;

        if(array[mid] == data_to_find)
        {
            return mid;
        }

        if(array[mid] < data_to_find)
        {
            res = RecurBinarySearch(array + mid + 1, arr_size/2 ,data_to_find);
            if(-1 == res)
            {
                return res;
            }
            else
            {
                return res + mid +1;
            }
        }
        else
        {
            return RecurBinarySearch(array , arr_size/2 ,data_to_find);
        }

    }
    return -1;
}

int MergeSort(void *arr_to_sort, size_t num_elements,
                    size_t elem_size, int(*is_before)
            (const void *elem1, const void *elem2))
{
    void *temp_arr = NULL;

    assert(arr_to_sort);
    assert(is_before);

    temp_arr = malloc(num_elements*elem_size);
    if(!temp_arr)
    {
        return -1;
    }

    RecurMergeSort(arr_to_sort, temp_arr, num_elements,elem_size, is_before);

    free(temp_arr);
    temp_arr = NULL;

    return 0;

}

static void RecurMergeSort(void *arr_to_sort, void *temp_arr, size_t num_elements,
     size_t elem_size, int(*is_before)(const void *elem1, const void *elem2))
{
    void *start = NULL;
    void *mid = NULL;
    int half_size = 0;



    if(num_elements > 1)
    {
        start = arr_to_sort;
        half_size = num_elements/2;
        mid = (char *)start + (elem_size * half_size);

        /*send left half*/
        RecurMergeSort(start, temp_arr, half_size, elem_size, is_before);
        /*send right half*/
        RecurMergeSort(mid, temp_arr, num_elements - half_size, elem_size, is_before);
        /*send to recursive merge function*/
        MergeHalves(start, mid, temp_arr, num_elements, elem_size, is_before);

    }

}

static void MergeHalves(void *left_start, void *right_start, void *temp_arr,
                                    size_t num_elements, size_t elem_size, 
                    int(*is_before)(const void *elem1, const void *elem2))
{
    char *left_arr = left_start;
    char *right_arr = right_start;

    char *right_arr_end = (char *)left_start + (num_elements*elem_size);
    char *temp_arr_start = temp_arr;

    while ((char *)left_start < right_arr && (char *)right_start < right_arr_end)
    {
    
        if(is_before(left_start, right_start))
        {
            memcpy(temp_arr, left_start, elem_size);
            left_start = (char *)left_start + elem_size;
        }
        else
        {
           memcpy(temp_arr, right_start, elem_size);
            right_start = (char *)right_start  + elem_size;
        }

        temp_arr = (char *)temp_arr + elem_size;
    }

    /*copy the rest of left side if any left*/
    memcpy(temp_arr, left_start, (right_arr - (char *)left_start));
    
     /*copy the rest of right side if any left*/
    memcpy(temp_arr, right_start, (right_arr_end - (char *)right_start));

    /*copy the sorted elelmnts from temp array to original array*/
    memcpy(left_arr, temp_arr_start, elem_size * num_elements);
}

int QuickSort(void *arr_to_sort, size_t num_elements, size_t elem_size,
                 int(*is_before)(const void *elem1, const void *elem2))
{

    void *temp_swap = NULL;

    assert(arr_to_sort);
    assert(is_before);

    temp_swap = malloc(elem_size);
    if(!temp_swap)
    {
        return -1;
    }

    RecurQuickSort(arr_to_sort, temp_swap, num_elements,elem_size, is_before);

    free(temp_swap);
    temp_swap = NULL;

    return 0;
}

static void RecurQuickSort(void *arr_to_sort, void *temp_swap,
                         size_t num_elements, size_t elem_size,
         int(*is_before)(const void *elem1, const void *elem2))
{
    void * pivot_pos = NULL;
    size_t pivot_index = 0;

    if(num_elements > 1)
    {
        pivot_index = QuickPartition(arr_to_sort, temp_swap, num_elements, elem_size, is_before);
        pivot_pos = (char *)arr_to_sort + (pivot_index * elem_size);
        /*send left half*/
        RecurQuickSort(arr_to_sort, temp_swap, pivot_index, elem_size, is_before);
        
        /*send right half*/
        RecurQuickSort((char *)pivot_pos, temp_swap,  num_elements - pivot_index, elem_size, is_before);

    }    
}

static size_t QuickPartition(void *arr_to_sort, void *temp_swap,
                            size_t num_elements, size_t elem_size,
            int(*is_before)(const void *elem1, const void *elem2))
{
    void *pivot = NULL;
    size_t high = num_elements -1;
    size_t low = 0;
    size_t start = -1;

    pivot = (char *)arr_to_sort + (high * elem_size );
   
    for(low = 0 ; low < high; ++low)
    {
        if(is_before((char *)arr_to_sort + (low * elem_size), pivot))
        {
            ++start;
            Swap((char *)arr_to_sort + (low * elem_size), (char *)arr_to_sort + (start * elem_size), temp_swap, elem_size);
        }

    }
        Swap((char *)arr_to_sort + ((start + 1) * elem_size),pivot, temp_swap, elem_size);

        return start + 1;

}

static void Swap(void *elem1, void *elem2, void *temp_swap, size_t elem_size)
{
    memcpy(temp_swap, elem1, elem_size);
    memcpy(elem1, elem2, elem_size);
    memcpy(elem2, temp_swap, elem_size);
}

























