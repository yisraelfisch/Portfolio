/*********************************
 * Reviewer: 
 * Author: 
 * File Name: merge_quick_test.c
 * ******************************/

#include <stdio.h>/*printf, puts*/
#include "merge_quick.h"

static int IntIsBefore(const void *elem1, const void *elem2);
static void PrintArr(size_t *arr, size_t size);

void BinarySearchIterativeCheck();
void BinarySearchRecurCheck();
void MergeTest();

int main()
{
    BinarySearchIterativeCheck();
    BinarySearchRecurCheck();
    MergeTest();
    return 0;
}

void BinarySearchIterativeCheck()
{
    int arr[7] = {1, 2, 3, 4, 10, 20, 30};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 1;
    int result = IterBinarySearch(arr,n, x);
    (result == -1) ? printf("Element is not present" " in array")
    : printf("Element is present at ""index %d\n",result);
}
void BinarySearchRecurCheck()
{
    int arr[7] = {1, 2, 3, 4, 10, 20, 30 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 1;
    int result = RecurBinarySearch(arr,n, x);
    (result == -1) ? printf("Element is not present" " in array")
    : printf("Element is present at ""index %d\n",result);
}

void MergeTest()
{
    size_t arr_to_sort[11] = {5, 1, 8, 2, 12, 14, 4, 3, 0, 18, 7};

    /*printf("Iter: %d\n", IterBinarySearch(array, 13 , 220));
    printf("Iter: %d\n", RecurBinarySearch(array, 13 , 220));*/

    PrintArr(arr_to_sort,11);

    QuickSort(arr_to_sort, 11, sizeof(size_t), IntIsBefore);

    PrintArr(arr_to_sort, 11);
}

static void PrintArr(size_t *arr, size_t size)
{
    size_t i = 0;

    puts(" ");
    for(i = 0; i < size; ++i)
    {
        printf("%ld\t", arr[i]);
    }
    puts(" ");
}




static int IntIsBefore(const void *elem1, const void *elem2)
{
    return *(size_t *)elem1 <= *(size_t *)elem2;
}
