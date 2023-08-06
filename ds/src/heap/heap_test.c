/*********************************
 * Reviewer: 				
 * Author: Yisrael Fisch			
 * File: heap_test.c				
 * ******************************/

#include <stdio.h>
#include "heap.h" 
#include "vector.h"

typedef struct person
{
    size_t idNum; 
    char *first_name;
} person_t;

static int AddToID(void *data, void *param)
{
      ((person_t *)data)->idNum += *(int *)param;
      return 0;
}
static int PersonCompare(const void* a, const void* b, void* user_param)
{
    size_t idNum1 = ((person_t *)a)->idNum;
    size_t idNum2 = ((person_t *)b)->idNum;
    (void)user_param;

    return idNum2 > idNum1;
}

static int IsPersonMatch(const void* a, const void* b, void* user_param)
{
    size_t idNum1 = ((person_t *)a)->idNum;
    size_t idNum2 = ((person_t *)b)->idNum;
    (void)user_param;

    return idNum2 - idNum1 == 0;
}
void CreateDestroyTest();
void PushTest();

int main()
{
    CreateDestroyTest();
    PushTest();

    return 0;
}

void CreateDestroyTest()
{
    
    heap_t *heap = NULL;
    int counter = 0;
    heap = HeapCreate(PersonCompare ,&counter);

    if(0 != HeapSize(heap))
    {
        printf("Error Line %d - Size\n", __LINE__);
    }

    if(1 != HeapIsEmpty(heap))
    {
        printf("Error Line %d - IsEmpty\n", __LINE__);
    }

    HeapDestroy(heap);
}

void PushTest()
{
    person_t a,b,c,d;
    int counter = 0;
    heap_t *heap = NULL;
    void *data = NULL;

    heap = HeapCreate(PersonCompare,&counter);
    a.idNum = 10;
    a.first_name = "Yuval";

    b.idNum = 9;
    b.first_name = "Amit";

    c.idNum = 2;
    c.first_name = "Maia";

    d.idNum = 8;
    d.first_name = "Adi";

    HeapPush(heap, &a);
    HeapPush(heap, &b);
    HeapPush(heap, &c);
    HeapPush(heap, &d);

    data = HeapPeek(heap);
    printf("%s\n", ((person_t *)data)->first_name); 
    if(4 != HeapSize(heap))
    {
        printf("Error Line %d - Size\n", __LINE__);
    }

    if(HeapIsEmpty(heap))
    {
        printf("Error Line %d - IsEmpty\n", __LINE__);
    }
    HeapPop(heap);
    data = HeapPeek(heap);
    printf("%s\n", ((person_t *)data)->first_name); 

    if(3 != HeapSize(heap))
    {
        printf("Error Line %d - Size\n", __LINE__);
    }

    data = HeapRemove(heap, &b, IsPersonMatch, NULL);
    printf("%s\n", ((person_t *)data)->first_name);

    data = HeapPeek(heap);
    printf("%s\n", ((person_t *)data)->first_name); 
    HeapDestroy(heap);
}
