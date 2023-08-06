/*********************************
 * Reviewer: Shani Horden
 * Author: Irit Ofir
 * File: bst_test.c
 * ******************************/

#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc, free, rand*/
#include <string.h> /*strcpy*/
#include <time.h> /* clock */
#include "bst.h"

typedef struct person
{
    size_t ID;
    char name[50];
} person_t;

static int PersonCompare(const void *person1, const void *person2, void* param)
{
    *(size_t *)param += 1;
    return *(size_t *)person2 - *(size_t *)person1;
}

int RandomNumCompare(const void *num1, const void *num2, void *param)
{
    *(size_t *)param += 1;
    return *(int *)num2 - *(int *)num1;
}

int TestGetData(person_t *person1, person_t *person2)
{
    return !strcmp(person1->name, person2->name);
}

static person_t PersonInit(size_t ID, char *name)
{
    person_t person = {0};
    person.ID = ID;
    strcpy(person.name, name);

    return person;
}

void TestCreate()
{
    bst_t *bst = NULL;

    bst = BSTCreate(PersonCompare, NULL);

    BSTDestroy(bst);
}

void TestInsert()
{
    bst_t *bst = NULL;
    person_t *student1 = NULL, *student2 = NULL, 
             *student3 = NULL, *bad_entry = NULL;
    bst_iterator_t iter1 = {0}, iter2 = {0}, iter3 = {0}, iter_bad_entry = {0};
    size_t student_count = 0;

    bst = BSTCreate(PersonCompare, &student_count);

    student1 = (person_t *)malloc(sizeof(person_t));
    if (!student1)
    {
        printf("Memory allocation failure on line %d\n", __LINE__);
        return;
    }

    *student1 = PersonInit(123456, "Irit");

    student2 = (person_t *)malloc(sizeof(person_t));
    if (!student2)
    {
        printf("Memory allocation failure on line %d\n", __LINE__);
        free(student1);
        return;
    }

    *student2 = PersonInit(01234, "Shani");

    student3 = (person_t *)malloc(sizeof(person_t));
    if (!student3)
    {
        printf("Memory allocation failure on line %d\n", __LINE__);
        free(student1);
        free(student2);
        return;
    }

    *student3 = PersonInit(7777777, "Yohai");

    bad_entry = (person_t *)malloc(sizeof(person_t));
    if (!bad_entry)
    {
        printf("Memory allocation failure on line %d\n", __LINE__);
        free(student1);
        return;
    }

    *bad_entry = PersonInit(01234, "Bad");

    iter1 = BSTInsert(bst, student1);
    iter2 = BSTInsert(bst, student2);
    iter3 = BSTInsert(bst, student3);
    iter_bad_entry = BSTInsert(bst, bad_entry);


    if(!BSTIsSameIter(iter2, BSTBegin(bst)))
    {
        printf("TestInsert failed (insert, begin) on line %d\n", __LINE__);
    }

    if(!BSTIsSameIter(iter1, BSTNext(BSTBegin(bst))))
    {
        printf("TestInsert failed (insert, next) on line %d\n", __LINE__);
    }

    if (!BSTIsSameIter(iter3, BSTPrev(BSTEnd(bst))))
    {
        printf("TestInsert failed (insert, prev, next) on line %d\n", __LINE__);
    }

    if (!BSTIsSameIter(iter_bad_entry, BSTEnd(bst)))
    {
        printf("TestInsert failed (insert, prev, next) on line %d\n", __LINE__);
    }

    if (BSTIsEmpty(bst))
    {
        printf("TestInsert failed (is empty) on line %d\n", __LINE__);
    }

    if (BSTSize(bst) != 3)
    {
        printf("TestInsert failed (size) on line %d\n", __LINE__);
    }

    /*BSTDestroy(bst);*/

    free(student1);
    free(student2);
    free(student3);
    free(bad_entry);

    BSTDestroy(bst);
}

void TestFind()
{
    bst_t *bst = NULL;
    person_t *student1 = NULL, *student2 = NULL, 
             *student3 = NULL, *find_data = NULL;
    bst_iterator_t iter1 = {0}, iter2 = {0}, iter3 = {0}, find_entry = {0};
    size_t student_count = 0;

    bst = BSTCreate(PersonCompare, &student_count);

    if (!BSTIsEmpty(bst))
    {
        printf("TestFind failed (is empty) on line %d\n", __LINE__);
    }

    student1 = (person_t *)malloc(sizeof(person_t));
    if (!student1)
    {
        printf("Memory allocation failure on line %d\n", __LINE__);
        return;
    }

    *student1 = PersonInit(123456, "Irit");

    student2 = (person_t *)malloc(sizeof(person_t));
    if (!student2)
    {
        printf("Memory allocation failure on line %d\n", __LINE__);
        free(student1);
        return;
    }

    *student2 = PersonInit(01234, "Shani");

    student3 = (person_t *)malloc(sizeof(person_t));
    if (!student3)
    {
        printf("Memory allocation failure on line %d\n", __LINE__);
        free(student1);
        free(student2);
        return;
    }

    *student3 = PersonInit(7777777, "Yohai");

    iter1 = BSTInsert(bst, student1);
    iter2 = BSTInsert(bst, student2);

    find_entry = BSTFind(bst, student2);
    find_data = BSTGetData(find_entry);

    if (!BSTIsSameIter(iter2, find_entry))
    {
        printf("TestFind failed on line %d\n", __LINE__);
    }

    find_entry = BSTFind(bst, student3);


    if (!BSTIsSameIter(BSTEnd(bst), find_entry))
    {
        printf("TestFind failed on line %d\n", __LINE__);
    }

    if (!TestGetData(find_data, student2))
    {
        printf("TestFind failed (get data) on line %d\n", __LINE__);
    }

    (void)iter1;
    (void)iter3;
 
    /*BSTDestroy(bst);*/

    free(student1);
    free(student2);
    free(student3);

    BSTDestroy(bst);
}

int SubParamFromNums(void *bst_data, void *user_param)
{
    if (*(int *)bst_data < *(int *)user_param)
    {
        *(int *)bst_data -= *(int *)user_param;
        return 0;
    }

    return 1;
}

void TestSeries()
{
    bst_t *bst = NULL;
    int rand_nums[25] = {0}, rand_low = 10, rand_high = 25, add_param = 0,
        first = 0, last = 0;
    bst_iterator_t iter = {0};
    size_t counter = 0, i = 0;

    bst = BSTCreate(RandomNumCompare, &counter);

    srand(clock());

    for (i = 0; i < sizeof(rand_nums) / sizeof(rand_nums[0]); ++i)
    {
        rand_nums[i] = rand()%(rand_high - rand_low) + rand_low;
        BSTInsert(bst, rand_nums + i);
        /*printf("%d ", rand_nums[i]);*/
    }

    /*printf("\n");*/

    counter = 0;

    for (iter = BSTNext(BSTBegin(bst));
         !BSTIsSameIter(iter, BSTEnd(bst));
         iter = BSTNext(iter))
    {
        if (*(int *)BSTGetData(iter) < *(int *)BSTGetData(BSTPrev(iter)))
        {
            printf("fail on %lu\n", counter);
        }
        /*printf("%d ", *(int *)BSTGetData(BSTPrev(iter)));*/
    }

    /*printf("%d ", *(int *)BSTGetData(BSTPrev(iter)));
    printf("\n");*/

    if(rand_high - rand_low <  (long)BSTSize(bst))
    {
        printf("TestSeries failed on line %d\n", __LINE__);
    }

    first = *(int *)BSTGetData(BSTBegin(bst));
    last = *(int *)BSTGetData(BSTPrev(BSTEnd(bst)));

    add_param = (rand_high - rand_low) / 2 + rand_low;
    BSTForEach(bst, SubParamFromNums, &add_param);

    if (*(int *)BSTGetData(BSTBegin(bst)) != first - add_param)
    {
        printf("TestSeries failed (foreach) on line %d\n", __LINE__);
    }

    if (*(int *)BSTGetData(BSTPrev(BSTEnd(bst))) != last)
    {
        printf("TestSeries failed (foreach) on line %d\n", __LINE__);
    }

    /*for (iter = BSTBegin(bst);
         !BSTIsSameIter(iter, BSTEnd(bst));
         iter = BSTNext(iter))
    {
        printf("%d ", *(int *)BSTGetData(iter));
    }
    printf("\n");*/
    
    BSTDestroy(bst);
}

void TestRemove()
{
    int array[17] = {100, 80, 200, 150, 40, 60, 30, 70, 250, 230, 300, 50, 10, 20, 170, 35, 280};
    bst_iterator_t iter[17] = {0}, find = {0}, find1 = {0}, find2 = {0};
    size_t counter = 0, i;
    bst_t *bst = NULL;

    bst = BSTCreate(RandomNumCompare, &counter);

    for (i = 0; i < sizeof(array) / sizeof(array[0]); ++i)
    {
        iter[i] = BSTInsert(bst, array + i);
    }

    BSTRemove(iter[4]); /* test remove iter with 2 children */

    find = BSTFind(bst, array + 4);
    if (!BSTIsSameIter(find, BSTEnd(bst)))
    {
        printf("TestRemove failed (get data on removed) on line %d\n", __LINE__);
    }

    find1 = BSTFind(bst, array + 6);
    find2 = BSTFind(bst, array + 15);
    
    if (!BSTIsSameIter(find2, BSTNext(find1)))
    {
        printf("TestRemove failed (next after remove) on line %d\n", __LINE__);
    }

    find2 = BSTFind(bst, array + 13);

    if (!BSTIsSameIter(find2, BSTPrev(find1)))
    {
        printf("TestRemove failed (prev after remove) on line %d\n", __LINE__);
    }

    BSTRemove(iter[1]); /* test remove iter with 1 child */

    find = BSTFind(bst, array + 1);
    if (!BSTIsSameIter(find, BSTEnd(bst)))
    {
        printf("TestRemove failed (get data on removed) on line %d\n", __LINE__);
    }

    BSTRemove(iter[7]); /* test remove no children */
    find = BSTFind(bst, array + 7);
    if (!BSTIsSameIter(find, BSTEnd(bst)))
    {
        printf("TestRemove failed (get data on removed) on line %d\n", __LINE__);
    }

    BSTRemove(iter[10]); /* test remove child and dummy */
    find = BSTFind(bst, array + 10);
    if (!BSTIsSameIter(find, BSTEnd(bst)))
    {
        printf("TestRemove failed (get data on removed) on line %d\n", __LINE__);
    }

    find = BSTFind(bst, array + 16);
    if (!BSTIsSameIter(find, BSTPrev(BSTEnd(bst))))
    {
        printf("TestRemove failed (get data on removed) on line %d\n", __LINE__);
    }

    BSTDestroy(bst);

}

int main()
{
	TestCreate();
    TestInsert();
    TestFind();
    TestSeries();
    TestRemove();
	return 0;
}