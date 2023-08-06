/*********************************
 * Reviewer: avigail
 * Author: yisrael fisch       
 * File: comparison_sorts.c
 * ******************************/

#include <assert.h>/*assert*/
#include "comparison_sorts.h"

static void Swap(int *index1, int *index2);
/*func to take the next unsorted number and replace it in the right place*/
static void InsretInSortedPlace(int *array, size_t sorted, size_t not_sorted);

void BubbleSort(int* array, size_t size)
{
    size_t i = 0, j = 0;
    assert(array);

    for (i = 0; i < size - 1; ++i)
    {
            
        for (j = 0; j < size - i - 1; ++j)
        {
            
            if (*(array + j) > *(array + j + 1))
            {
                Swap(array + j, array + j + 1);
            }
        }
    }
}


void InsertionSort(int* array, size_t size)
{
    size_t not_sorted = 0;
    size_t sorted = 0; 
    assert(array);

    for(sorted = 0; sorted < size -1; ++sorted)
    {
        not_sorted = sorted + 1;

        if(*(array + sorted) > *(array + not_sorted))
        {
           InsretInSortedPlace(array, sorted, not_sorted);

        }
    }

}


void SelectionSort(int* array, size_t size)
{
    size_t swap_index = 0 , i = 0;
    size_t min_index = 0;
    assert(array);

    for(swap_index = 0; swap_index < size -1; ++swap_index)
    {
        min_index = swap_index;

        for(i = swap_index + 1; i < size; ++i)
        {
            if(*(array + i) < *(array + min_index))
            {
                min_index = i;
            }
        }

        if(*(array + min_index) < *(array + swap_index))/*meybe unessery*/
        {
            Swap(array + swap_index, array + min_index);
        }
    }
}

void Swap(int *index1, int *index2)
{
    int temp = *index1;
    *index1 = *index2;
    *index2 = temp;
}

static void InsretInSortedPlace(int *array, size_t sorted, size_t not_sorted)
{
   int temp = *(array + not_sorted);
    while((size_t)-1 != sorted && *(array + sorted) > temp)
    {
        *(array + sorted + 1) = *(array + sorted);
        sorted -= 1;
    }

        *(array + sorted + 1) = temp;
}
