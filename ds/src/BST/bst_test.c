/*********************************
 * Reviewer: 
 * Author:     
 * File: bst_test.h
 * ******************************/

#include <stdio.h>/*printf, puts*/
#include "bst.h"
#include <stdlib.h> /*malloc free*/




typedef struct person
{
    size_t idNum; /*key*/
    char *first_name; /*value*/
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

    return idNum2 - idNum1;
}

void CreateDestroyTest();
void RemoveTest();
void ForEachCheck();

int main()
{
    
    CreateDestroyTest(); 
    RemoveTest();
    ForEachCheck();
    return 0;   
}


void CreateDestroyTest()
{

    bst_t *bst = NULL;
    void *data = NULL;
    bst_iterator_t iter;
    person_t a,b,c,d,e;

    bst = BSTCreate(PersonCompare, NULL); 
    if(0 == BSTIsEmpty(bst))
    {
      puts("isempty eror-1");
    }
    if(BSTSize(bst))
    {
      puts("size eror-1");
    }

    a.idNum = 234548352;
    a.first_name = "Yuval";

    b.idNum = 328954777;
    b.first_name = "Amit";

    c.idNum = 123456687;
    c.first_name = "Maia";

    d.idNum = 345668777;
    d.first_name = "Adi";

    e.idNum = 213121222;
    e.first_name = "nobody";
    
    BSTInsert(bst, &a);   
    BSTInsert(bst, &b); 
    BSTInsert(bst, &c);
    if(1 == BSTIsEmpty(bst))
    {
      puts("isempty eror-2");
    }
    if(3 != BSTSize(bst))
    {
      puts("size eror-2");
    }
    iter = BSTInsert(bst, &d);
    data = BSTGetData(iter);
    printf("%s\n", ((person_t *)data)->first_name); 

    iter = BSTFind(bst, &c);
    data = BSTGetData(iter);
    printf("%s\n", ((person_t *)data)->first_name);   
    
    iter = BSTBegin(bst);
    data = BSTGetData(iter);
    printf("%s\n", ((person_t *)data)->first_name);

    iter = BSTEnd(bst);
    if(BSTGetData(iter))
    {
    puts("bst end error");
    }

    iter = BSTFind(bst, &e);/*find somthing that not exist in the tree*/
    if(BSTGetData(iter))
    {
    puts("bst end/find error");
    }

    puts("-----next check ------");
    iter = BSTFind(bst, &b);
    data = BSTGetData(iter);
    printf("%s\n", ((person_t *)data)->first_name); 
    iter = BSTNext(iter);
    data = BSTGetData(iter);
    printf("%s\n", ((person_t *)data)->first_name);

    iter = BSTBegin(bst);
    data = BSTGetData(iter);
    printf("%s\n", ((person_t *)data)->first_name); 
    iter = BSTNext(iter);
    data = BSTGetData(iter);
    printf("%s\n", ((person_t *)data)->first_name);

    puts("-----prev check ------");
    iter = BSTFind(bst, &b);
    data = BSTGetData(iter);
    printf("%s\n", ((person_t *)data)->first_name); 
    iter = BSTPrev(iter);
    data = BSTGetData(iter);
    printf("%s\n", ((person_t *)data)->first_name);

    iter = BSTEnd(bst);
    data = BSTGetData(iter);
    printf("we are at the end\n");  
    iter = BSTPrev(iter);
    data = BSTGetData(iter);
    printf("%s\n", ((person_t *)data)->first_name);

    puts("-----same iter check ------");
    iter = BSTBegin(bst);
    if(0 == BSTIsSameIter(iter, BSTBegin(bst)))
    {
        puts("same iter error-1");
    }

    if(1 == BSTIsSameIter(iter, BSTNext(iter)))
    {
        puts("same iter error-2");
    }
    BSTDestroy(bst); 
}

void RemoveTest()
{
    bst_t *bst = NULL;
    void *data = NULL;
    bst_iterator_t iter;
    person_t a,b,c,d;

    bst = BSTCreate(PersonCompare, NULL); 

    a.idNum = 234548352;
    a.first_name = "Yuval";

    b.idNum = 328954777;
    b.first_name = "Amit";

    c.idNum = 123456687;
    c.first_name = "Maia";

    d.idNum = 345668777;
    d.first_name = "Adi";


    
    puts("-----remove check-----");
    BSTInsert(bst, &a);   
    BSTInsert(bst, &b); 
    BSTInsert(bst, &c);
    if(1 == BSTIsEmpty(bst))
    {
      puts("isempty eror-2");
    }
    iter = BSTInsert(bst, &d);
    BSTRemove(iter);
    if(3 != BSTSize(bst))
    {
      puts("size/remove eror-3");
    }
    iter = BSTPrev(BSTEnd(bst));
    data = BSTGetData(iter);
    printf("%s\n", ((person_t *)data)->first_name);
    puts("----amit is good------");


    iter = BSTFind(bst, &a);/*yuval*/
    BSTRemove(iter);
    iter = BSTBegin(bst);
    data = BSTGetData(iter);
    printf("%s\n", ((person_t *)data)->first_name);
    puts("----maia is good------");    
    
    iter = BSTFind(bst, &c);/*maia*/
    BSTRemove(iter);
    printf("%s\n", ((person_t *)data)->first_name);
    puts("----maia is good------");
    iter = BSTBegin(bst);
    data = BSTGetData(iter);
    printf("%s\n", ((person_t *)data)->first_name);
    puts("----amit is good------");

    BSTRemove(iter);
    if(0 != BSTSize(bst))
    {
      puts("size/remove eror-4");
    }

    BSTDestroy(bst);    
}

void ForEachCheck()
{
    bst_t *bst = NULL;
    void *data = NULL;
    int param = 10;
    bst_iterator_t iter;
    person_t a,b,c,d;

    bst = BSTCreate(PersonCompare, NULL); 

    a.idNum = 234548352;
    a.first_name = "Yuval";

    b.idNum = 328954777;
    b.first_name = "Amit";

    c.idNum = 123456687;
    c.first_name = "Maia";

    d.idNum = 345668777;
    d.first_name = "Adi";


    
    puts("-----for each check-----");
    BSTInsert(bst, &a);   
    BSTInsert(bst, &b); 
    BSTInsert(bst, &c);
    BSTInsert(bst, &d);

    iter = BSTFind(bst, &a);
    data = BSTGetData(iter);
    printf("yuval id before is: %lu\n", ((person_t *)data)->idNum);

    iter = BSTFind(bst, &b);
    data = BSTGetData(iter);
    printf("amit id before is: %lu\n", ((person_t *)data)->idNum);

    iter = BSTFind(bst, &c);
    data = BSTGetData(iter);
    printf("maia id before is: %lu\n", ((person_t *)data)->idNum);

    iter = BSTFind(bst, &d);
    data = BSTGetData(iter);
    printf("adi id before is: %lu\n", ((person_t *)data)->idNum);

    BSTForEach(bst, AddToID, &param);
    puts("---after add 10 for each");

    iter = BSTFind(bst, &a);
    data = BSTGetData(iter);
    printf("yuval id after is: %lu\n", ((person_t *)data)->idNum);

    iter = BSTFind(bst, &b);
    data = BSTGetData(iter);
    printf("amit id after is: %lu\n", ((person_t *)data)->idNum);

    iter = BSTFind(bst, &c);
    data = BSTGetData(iter);
    printf("maia id after is: %lu\n", ((person_t *)data)->idNum);

    iter = BSTFind(bst, &d);
    data = BSTGetData(iter);
    printf("adi id after is: %lu\n", ((person_t *)data)->idNum);
    BSTDestroy(bst);
}


  

