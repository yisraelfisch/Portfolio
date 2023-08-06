/*********************************
 * Reviewer: avigail
 * Author: yisrael fisch       
 * File: linear_sort.h
 * ******************************/

#include <stdlib.h> /*calloc, free*/
#include <assert.h> /*assert*/
#include "linear_sorts.h"

static void CountingSortForRadix(int* array, size_t size, int place);
static int MaxValue(int * array, size_t size);


void CountingSort(int* array, size_t size)
{
    int *count_arr = NULL;
    int *output_arr = NULL;
    int max = 0;
    size_t i = 0;
    assert(array);
    
    output_arr = (int *)calloc(size + 1, sizeof(int));
    if(!output_arr)
    {
        return;
    }
    max = MaxValue(array, size);

    count_arr = (int *)calloc(max + 1, sizeof(int));
    if(!count_arr)
    {
        free(output_arr);
        return;
    }

    for (i = 0; i < size; i++)
    {
        ++count_arr[array[i]];
    }

    for (i = 1; i <= (size_t)max; i++)
    {
        count_arr[i] += count_arr[i - 1];
    }

    for (i = size - 1; (int)i >= 0; i--) 
    {
        output_arr[count_arr[array[i]] - 1] = array[i];
        --count_arr[array[i]];
    }    

    for (i = 0; i < size; i++)
    {
        array[i] = output_arr[i];
    }
    free(count_arr);
    free(output_arr);
}

void RadixSort(int* array, size_t size)
{

    int max = 0;
    int place = 1;
    assert(array);
    max = MaxValue(array, size);

    for (place = 1; max / place > 0; place *= 10)
    {
        CountingSortForRadix(array, size, place);
    }

}

static int MaxValue(int * array, size_t size)
{
    int max = array[0];
    size_t i = 0;
    for (i = 1; i < size; i++) 
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }

    return max;
}

static void CountingSortForRadix(int* array, size_t size, int place)
{
    int *count_arr = NULL;
    int *output_arr = NULL;
    int max = (array[0] / place) % 10;
    size_t i = 0;
    assert(array);
    
    output_arr = (int *)calloc(size + 1, sizeof(int));
    if(!output_arr)
    {
        return;
    }

    for (i = 1; i < size; i++) 
    {
        if (((array[i] / place) % 10) > max)
        {
            max = array[i];
        }
    }

    count_arr = (int *)calloc(max + 1, sizeof(int));
    if(!count_arr)
    {
        free(output_arr);
        return ;
    }

    for (i = 0; i < size; i++)
    {
        ++count_arr[(array[i] / place) % 10];
    }

    for (i = 1; i <= (size_t)max; i++)
    {
        count_arr[i] += count_arr[i - 1];
    }

    for(i = size - 1; (int)i >= 0; i--) 
    {
        output_arr[count_arr[(array[i] / place) % 10] - 1] = array[i];
        --count_arr[(array[i] / place) % 10];
    }    

    for (i = 0; i < size; i++)
    {
        array[i] = output_arr[i];
    }

    free(count_arr);
    free(output_arr);
}
