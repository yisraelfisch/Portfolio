/*********************************
 * Reviewer: Daniel.b
 * Author: yisrael fisch       
 * File: dll_test.c
 * ******************************/


#include <stdio.h>  /*printf*/
#include <string.h> /*strcmp*/
#include "dll.h"

void TestDLLBasic(void);
void TestDLLInsertRemove(void);
void TestDLLFindMultiFind(void);
void TestDLLSplice(void);
void TestForEach(void);
int IsEqual(const void *list_data, const void *data);
int IsBigger(const void *list_data, const void *data);
int AddParam(void *list_data, void *param);

int main(void)
{
    TestDLLBasic();
    TestDLLInsertRemove();
    TestDLLFindMultiFind();
    TestDLLSplice();
    TestForEach();
    return 0;
}


void TestDLLBasic(void)
{
    dll_t *dlist = DListCreate();
    dll_iterator_t iter = DListBegin(dlist);
    char *str = "hello", *test = {'\0'};

    if(!DListIsEmpty(dlist))
    {
        printf("Error 1: Created List isn't empty\n");
    }

    if(DListSize(dlist))
    {
        printf("Error 2: Created list size isn't zero\n");
    }

    iter = DListInsert(dlist, iter, str);

    if(DListIsEmpty(dlist))
    {
        printf("Error 3: List is empty after insert\n");
    }

    if(1 != DListSize(dlist))
    {
        printf("Error 4: List size isn't 1 after 1 insert\n");
    }

    test = (char *)DListGetData(iter);

    if (strcmp(str,test))
    {
        printf("Error 5: Get Data incorrect\n");
    }

    iter = DListRemove(iter);

    if(!DListIsEmpty(dlist))
    {
        printf("Error 6: List isn't empty after remove\n");
    }

    if(DListSize(dlist))
    {
        printf("Error 7: Size isn't zero after remove\n");
    }

    if(!DListIsSameIter(iter, DListEnd(dlist)))
    {
        printf("Error 8: iter isn't the last node\n");
    }

    DListDestroy(dlist);
}

void TestDLLInsertRemove(void)
{
    dll_t *dlist = DListCreate();
    dll_iterator_t iter = DListBegin(dlist);
    int a = 1, b = 2, c = 3, d = 4, e = 5, x = 20, z = 50;

    iter = DListInsert(dlist, iter, &e);
    iter = DListInsert(dlist, iter, &d);
    iter = DListInsert(dlist, iter, &c);
    iter = DListInsert(dlist, iter, &b);
    iter = DListInsert(dlist, iter, &a);

    iter = DListBegin(dlist);
    if (a != *(int *)DListGetData(iter))
    {
        printf("Error 9: insert not correct order\n");
    }

    iter = DListNext(iter);

    if (b != *(int *)DListGetData(iter))
    {
        printf("Error 10: insert not correct order\n");
    }

    iter = DListNext(iter);
    iter = DListPrev(iter);

    if (b != *(int *)DListGetData(iter))
    {
        printf("Error 11: insert not correct order\n");
    }

    iter = DListPushFront(dlist, &x);
    iter = DListPushBack(dlist, &z);

    if(x != *(int *)DListPopFront(dlist))
    {
        printf("Error 12: PushFront or PopFront\n");
    }

    if(z != *(int *)DListPopBack(dlist))
    {
        printf("Error 13: PushBack or PopBack\n");
    }

    if(5 != DListSize(dlist))
    {
        printf("Error 14: incompatible number of nodes\n");
    }

    DListDestroy(dlist);
}

void TestDLLFindMultiFind(void)
{
    dll_t *dlist1 = DListCreate();
    dll_t *dlist2 = DListCreate();
    dll_iterator_t iter1 = DListBegin(dlist1);
    dll_iterator_t iter_find = NULL;
    int a = 245, b = 42, c = 3, d = 19, e = 5, f = 20, g = 50, h = -49;

    iter1 = DListInsert(dlist1, iter1, &h);
    iter1 = DListInsert(dlist1, iter1, &g);
    iter1 = DListInsert(dlist1, iter1, &f);
    iter1 = DListInsert(dlist1, iter1, &e);
    iter1 = DListInsert(dlist1, iter1, &d);
    iter1 = DListInsert(dlist1, iter1, &c);
    iter1 = DListInsert(dlist1, iter1, &b);
    iter1 = DListInsert(dlist1, iter1, &a);

    iter_find = DListFind(DListBegin(dlist1), DListEnd(dlist1), &g, IsEqual);

    if (!DListIsSameIter(iter_find, DListPrev(DListPrev(DListEnd(dlist1)))))
    {
        printf("Error 15: DListFind\n");
    }

    if(DListMultiFind(DListBegin(dlist1), DListEnd(dlist1), dlist2, &d, IsBigger))
    {
        printf("Error 16: DListMultiFind\n");
    }

    if(4 != DListSize(dlist2))
    {
        printf("Error 17: DListMultiFind\n");
    }

    DListDestroy(dlist1);
    DListDestroy(dlist2);
}

void TestDLLSplice(void)
{
    dll_t *dlist1 = DListCreate();
    dll_t *dlist2 = DListCreate();
    dll_iterator_t iter1 = DListBegin(dlist1);
    dll_iterator_t iter2 = DListBegin(dlist2);
    dll_iterator_t iter_from = NULL;
    dll_iterator_t iter_to = NULL;
    dll_iterator_t iter_where = NULL;
    dll_iterator_t iter_spliced = NULL;

    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7, h = 8;
    int x = 10, y = 20, z = 30;

    iter1 = DListInsert(dlist1, iter1, &h);
    iter1 = DListInsert(dlist1, iter1, &g);
    iter1 = DListInsert(dlist1, iter1, &f);
    iter1 = DListInsert(dlist1, iter1, &e);
    iter1 = DListInsert(dlist1, iter1, &d);
    iter1 = DListInsert(dlist1, iter1, &c);
    iter1 = DListInsert(dlist1, iter1, &b);
    iter1 = DListInsert(dlist1, iter1, &a);

    iter_from = DListFind(DListBegin(dlist1), DListEnd(dlist1), &b, IsEqual);
    iter_to = DListFind(DListBegin(dlist1), DListEnd(dlist1), &g, IsEqual);

    iter2 = DListInsert(dlist2, iter2, &z);
    iter2 = DListInsert(dlist2, iter2, &y);
    iter2 = DListInsert(dlist2, iter2, &x);

    iter_where = DListFind(DListBegin(dlist2), DListEnd(dlist2), &y, IsEqual);

    iter_spliced = DListSplice(iter_where, iter_from, iter_to);

    if (8 != DListSize(dlist2))
    {
        printf("Error 18: DListSplice\n");
    }

    if (3 != DListSize(dlist1))
    {
        printf("Error 19: DListSplice\n");
    }

    if(!DListIsSameIter(iter_spliced, DListBegin(dlist2)))
    {
        printf("Error 20: DListSplice\n");
    }

    /*if you are curious, uncomment the next lines to print new lists*/

    iter1 = DListBegin(dlist1);
    printf("dlsit1:\n");
    printf("%d\n", *(int *)DListGetData(iter1));
    iter1 = DListNext(iter1);
    printf("%d\n", *(int *)DListGetData(iter1));
    iter1 = DListNext(iter1);
    printf("%d\n", *(int *)DListGetData(iter1));


    printf("\ndlist2:\n");
    printf("%d\n", *(int *)DListGetData(iter_spliced));
    iter_spliced = DListNext(iter_spliced);
    printf("%d\n", *(int *)DListGetData(iter_spliced));
    iter_spliced = DListNext(iter_spliced);
    printf("%d\n", *(int *)DListGetData(iter_spliced));
    iter_spliced = DListNext(iter_spliced);
    printf("%d\n", *(int *)DListGetData(iter_spliced));
    iter_spliced = DListNext(iter_spliced);
    printf("%d\n", *(int *)DListGetData(iter_spliced));
    iter_spliced = DListNext(iter_spliced);
    printf("%d\n", *(int *)DListGetData(iter_spliced));
    iter_spliced = DListNext(iter_spliced);
    printf("%d\n", *(int *)DListGetData(iter_spliced));
    iter_spliced = DListNext(iter_spliced);
    printf("%d\n", *(int *)DListGetData(iter_spliced));
    iter_spliced = DListNext(iter_spliced);

    DListDestroy(dlist1);
    DListDestroy(dlist2);
}

void TestForEach(void)
{
    dll_t *dlist = DListCreate();
    dll_iterator_t iter_begin = DListBegin(dlist);
    dll_iterator_t iter1 = NULL;
    dll_iterator_t iter2 = NULL;
    dll_iterator_t iter3 = NULL;
    dll_iterator_t iter4 = NULL;
    dll_iterator_t iter5 = NULL;
    int a = 1, b = 2, c = 3, d = 4, e = 5;
    int param = 8;
    int a_test = a+param, b_test = b+param, c_test = c+param, d_test = d+param;

    iter5 = DListInsert(dlist, iter_begin, &e);
    iter4 = DListInsert(dlist, iter5, &d);
    iter3 = DListInsert(dlist, iter4, &c);
    iter2 = DListInsert(dlist, iter3, &b);
    iter1 = DListInsert(dlist, iter2, &a);

    if (DListForEach(iter1, iter5, &param, AddParam))
    {
        printf("Error 21: DListForEach\n");
    }

    if(a != a_test || b != b_test || c != c_test || d != d_test)
    {
        printf("Error 22: DListForEach didn't perform correctly\n");
    }

    DListDestroy(dlist);
}

int IsEqual(const void *list_data, const void *data)
{
    return !(list_data == data);
}

int IsBigger(const void *list_data, const void *data)
{
    return !(list_data > data);
}

int AddParam(void *list_data, void *param)
{
    *(int *)list_data += *(int *)param;
    return 0;
}
