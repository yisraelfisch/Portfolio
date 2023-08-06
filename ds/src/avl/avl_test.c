/*************************************** 
file name: avl.h
Author: yisrael fisch
*reviewer: sara
******************************************/

#include <stdlib.h> /*malloc, free*/
#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/
#include "avl.h"

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

void CeateTest();
void ForEachTest();

int main ()
{
	CeateTest();
	ForEachTest();
	return 0;
}

void CeateTest()
{
	avl_t *avl = NULL;


    void *data = NULL;
    size_t height = 0;
    person_t a,b,c,d,e;

     
    avl = AvlCreate(PersonCompare, NULL);
    if(0 == AvlIsEmpty(avl))
    {
      puts("isempty eror-1");
    }
    if(AvlSize(avl))
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

    AvlInsert(avl, &a);
    height = AvlHeight(avl);
    printf("%lu\n", height);
    
    AvlInsert(avl, &b); 
    height = AvlHeight(avl);
    printf("%lu\n", height);
    
    AvlInsert(avl, &d);
    height = AvlHeight(avl);
    printf("%lu\n", height);
    if(1 == AvlIsEmpty(avl))
    {
      puts("isempty eror-2");
    }
    if(3 != AvlSize(avl))
    {
      puts("size eror-2");
    }
    

    data  = AvlFind(avl, &d);
  
    printf("%s\n", ((person_t *)data)->first_name);   
    
 
 	AvlDestroy(avl);
}

void ForEachTest()
{
	avl_t *avl = NULL;

    int  param = 10;
    void *data = NULL;
    size_t height = 0;
    person_t a,b,c,d,e;

     
    avl = AvlCreate(PersonCompare, NULL);
    if(0 == AvlIsEmpty(avl))
    {
      puts("isempty eror-1");
    }
    if(AvlSize(avl))
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

    AvlInsert(avl, &a);
    height = AvlHeight(avl);
    printf("%lu\n", height);
    
    AvlInsert(avl, &b); 
    height = AvlHeight(avl);
    printf("%lu\n", height);
    
    AvlInsert(avl, &d);
    height = AvlHeight(avl);
    printf("%lu\n", height);
    if(1 == AvlIsEmpty(avl))
    {
      puts("isempty eror-2");
    }
    if(3 != AvlSize(avl))
    {
      puts("size eror-2");
    }
    

    data  = AvlFind(avl, &d);
	printf("adi id before is: %lu\n", ((person_t *)data)->idNum);  


    data  = AvlFind(avl, &a);
	printf("yuval id before is: %lu\n", ((person_t *)data)->idNum);  


    data  = AvlFind(avl, &b);
	printf("amit id before is: %lu\n", ((person_t *)data)->idNum);  
    
    AvlForEach(avl, AddToID, &param);
    puts("---after add 10 for each");

    data  = AvlFind(avl, &d);
	printf("adi id before is: %lu\n", ((person_t *)data)->idNum);  


    data  = AvlFind(avl, &a);
	printf("yuval id before is: %lu\n", ((person_t *)data)->idNum);  


    data  = AvlFind(avl, &b);
	printf("amit id before is: %lu\n", ((person_t *)data)->idNum);  
       

 	AvlDestroy(avl);
}







