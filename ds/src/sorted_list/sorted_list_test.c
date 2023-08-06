/*********************************
 * Reviewer: 
 * Author: yisrael fisch       
 * File: sorted_list_test.c
 * ******************************/

#include <stdio.h>/*printf*/
#include "sorted_list.h"

void CheckCreate();
void Checkinsert();
void CheckFindIf();
void CheckForEach();
void MergeTest();
int compare(const void *data1,const void *data2, void *user_param);
int AddParam(void *list_data, void *param);
int IsEqual(const void *list_data, const void *data);

int main ()
{
    CheckCreate();
    Checkinsert();
    CheckFindIf();
    CheckForEach();
    MergeTest();
    return 0;
}


void CheckCreate()
{

    sorted_list_compare_func_t compare_func = compare ; 
    sorted_list_t *check =  SortedListCreate(compare_func, NULL);

    if(SortedListBegin(check).iter != SortedListEnd(check).iter)
    {
        printf("create error(1)\n");
    }

    if(0 == SortedListIsEmpty(check))
    {
        printf("create error(2)\n");
    }
    if(0 != SortedListSize(check))
    {
        printf("size error(3)\n");
    }
    SortedListDestroy(check);
}


void Checkinsert()
{
    sorted_list_compare_func_t compare_func = compare; 
    sorted_list_t *check =  SortedListCreate(compare_func, NULL);

    sorted_list_iterator_t iter =  SortedListIterInit();
    int a = 1, b = 2, c = 3, d = 4, e = 5, x = 20, z = 50;

    iter = SortedListInsert(check, &e);
    iter = SortedListInsert(check, &d);
    iter = SortedListInsert(check, &c);
    iter = SortedListInsert(check, &b);
    iter = SortedListInsert(check, &a); 

    if(a != *(int *)SortedListGetData(SortedListBegin(check)))
    {
        printf("insert error (4)\n");
    } 

    iter = SortedListRemove(SortedListBegin(check));

    if(b != *(int *)SortedListGetData(SortedListBegin(check)))
    {
        printf("insert error (5)\n");
    } 

    iter = SortedListRemove(SortedListBegin(check));


    if(d != *(int *)SortedListGetData(SortedListNext(iter)))
    {
        printf("insert error (6)\n");
    } 

    iter = SortedListInsert(check, &x);

     if(e != *(int *)SortedListGetData(SortedListPrev(iter)))
    {
        printf("insert error (7)\n");
    } 

     iter = SortedListInsert(check, &z);

     if(x != *(int *)SortedListGetData(SortedListPrev(iter)))
    {
        printf("insert error (8)\n");
    } 

    SortedListDestroy(check);

}

void CheckFindIf()
{
    sorted_list_compare_func_t compare_func = compare; 
    sorted_list_t *check = SortedListCreate(compare_func, NULL);
    sorted_list_iterator_t iter =  SortedListIterInit();
    sorted_list_iterator_t iter1 =  SortedListIterInit();
    int a = 1, b = 2, c = 3, d = 4, e = 5;
    iter.list = check;
    iter1.list = check;

    iter = SortedListInsert(check, &e);
    iter = SortedListInsert(check, &d);
    iter = SortedListInsert(check, &c);
    iter = SortedListInsert(check, &b);
    iter = SortedListInsert(check, &a);

    iter1 = SortedListFindIf(SortedListBegin(check), SortedListEnd(check), &a, IsEqual);
    if(*(int *)SortedListGetData(iter) != *(int *)SortedListGetData(iter1))
    {
        printf("SortedListFindIf error (9)");
    }

    SortedListDestroy(check);

}

void CheckForEach()
{
    sorted_list_compare_func_t compare_func = compare; 
    sorted_list_t *check =  SortedListCreate(compare_func, NULL);

    
    
    int a = 1, b = 2, c = 3, d = 4, e = 5;
    int param = 8;
    int a_test = a+param, b_test = b+param, c_test = c+param, d_test = d+param;
   

    SortedListInsert(check, &e);
    SortedListInsert(check, &d);
    SortedListInsert(check, &c);
    SortedListInsert(check, &b);
    SortedListInsert(check, &a);

    if(SortedListForEach(SortedListBegin(check), SortedListEnd(check), &param, AddParam))
    {
        printf("SortedListForEach error (10)\n");
    }    
    if(a != a_test || b != b_test || c != c_test || d != d_test)
    {
        printf("SortedListForEach didn't perform correctly (11)\n");
    }

    SortedListDestroy(check);
}

void MergeTest()
{
    sorted_list_compare_func_t compare_func = compare; 
    sorted_list_t *list1 =  SortedListCreate(compare_func, NULL);

    sorted_list_t *list2 =  SortedListCreate(compare_func, NULL);

    sorted_list_iterator_t iter =  SortedListIterInit();

    int x = 4, y = 6, z = 8, t = 20, m = 30;
    int a = 1, b = 2, c = 11, d = 40;

    iter = SortedListBegin(list2);

    SortedListInsert(list1, &m);
    SortedListInsert(list1, &t);
    SortedListInsert(list1, &z);
    SortedListInsert(list1, &y);
    SortedListInsert(list1, &x);

    SortedListInsert(list2, &a);
    SortedListInsert(list2, &c);
    SortedListInsert(list2, &d);
    SortedListInsert(list2, &b);

    SortedListMerge(list2, list1); /*list2 - is dest, list1 - is src*/

    iter = SortedListNext(SortedListNext(SortedListBegin(list2)));

    if(4 != *((int *)SortedListGetData(iter)))
    {
        printf("Error 11: SortedListMerge\n");
    }

    if((size_t)9 != SortedListSize(list2))
    {
        printf("Error 11: SortedListMerge\n");
    }

    if(1 != SortedListIsEmpty(list1))
    {
        printf("Error 12: SortedListMerge\n");
    }

    SortedListDestroy(list1);
    SortedListDestroy(list2);

}
int compare(const void *data1,const void *data2, void *user_param)
{

    if(*(int *)data1 > *(int *)data2)
    {
        return -1;
    }

    if(*(int *)data1 < *(int *)data2)
    {
        return 1;
    }

    return 0;
}

int IsEqual(const void *list_data, const void *data)
{
    return !(list_data == data);
}

int AddParam(void *list_data, void *param)
{
    *(int *)list_data += *(int *)param;
    return 0;
}