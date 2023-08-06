/*********************************
 * Reviewer: shani
 * Author: yisrael fisch
 * File Name: hash_table_test.c
 * ******************************/

#include <stdio.h>
#include "hash_table.h"

typedef struct person
{
    size_t idNum; /*key*/
    char *first_name; /*value*/
} person_t;

int IsEqual(const void *list_data, const void *data)
{
    char idNum1 = ((person_t *)list_data)->idNum;
    char idNum2 = ((person_t *)data)->idNum;
   
    return !(idNum2 == idNum1);
}

int HashFunc(void *key)
{
	return (((person_t *)key)->idNum);
}

int IsBigger(const void *list_data, const void *data)
{
    return !(list_data > data);
}

static int AddToID(void *data, void *param)
{
      ((person_t *)data)->idNum += *(int *)param;
      return 0;
}

void TestCreate();
void TestAll();
void TestForEach();

int main()
{
	TestCreate();
	TestAll();
	TestForEach();
	return 0;
}

void TestCreate()
{
 	hash_t * hash = NULL;
 	size_t size = 10;
 	
 	hash = HashCreate(IsEqual, HashFunc, size);

 	if(!HashIsEmpty(hash))
    {
        printf("Error 1: Created hash isn't empty\n");
    }

    if(HashSize(hash))
    {
        printf("Error 2: Created hash size isn't zero\n");
    }

 	HashDestroy(hash);

}

void TestAll()
{
	void *data = NULL;
	hash_t * hash = NULL;
 	size_t size = 10;
 	person_t a,b,c,d,e;
 	hash = HashCreate(IsEqual, HashFunc, size);
	
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

 	HashInsert(hash, &a);
 	HashInsert(hash, &b);
 	HashInsert(hash, &c);
 	HashInsert(hash, &d);
 	if(HashIsEmpty(hash))
    {
        printf("Error 3: hash isn't empty\n");
    }

    if(4 != HashSize(hash))
    {
        printf("Error 4: hash size isn't zero\n");
    }
    data  = HashFind(hash, &d);
  
  	puts("check find print adi\n");
    printf("%s\n", ((person_t *)data)->first_name);

    data  = HashFind(hash, &c);
  
  	puts("check find print maia\n");
    printf("%s\n", ((person_t *)data)->first_name);

	HashRemove(hash, &a);
	HashRemove(hash, &b);
	HashRemove(hash, &c);
	HashRemove(hash, &e);/*not in the list*/

	if(HashIsEmpty(hash))
    {
        printf("Error 5: hash isn't empty\n");
    }

	if(1 != HashSize(hash))
    {
        printf("Error 6: hash size is 1\n");
    }

	HashRemove(hash, &d);    
	
	if(!HashIsEmpty(hash))
    {
        printf("Error 7: hash is empty\n");
    }

	if(0 != HashSize(hash))
    {
        printf("Error 6: hash size is 0\n");
    }

 	HashDestroy(hash);

}

void TestForEach()
{
	void *data = NULL;
	hash_t * hash = NULL;
 	size_t size = 10;
 	size_t ten = 10;
 	person_t a,b,c,d;
 	hash = HashCreate(IsEqual, HashFunc, size);
	
	a.idNum = 234548352;
    a.first_name = "Yuval";

    b.idNum = 328954777;
    b.first_name = "Amit";

    c.idNum = 123456687;
    c.first_name = "Maia";

    d.idNum = 345668777;
    d.first_name = "Adi";


 	HashInsert(hash, &a);
 	HashInsert(hash, &b);
 	HashInsert(hash, &c);
 	HashInsert(hash, &d);
 	if(HashIsEmpty(hash))
    {
        printf("Error 3: hash isn't empty\n");
    }

    if(4 != HashSize(hash))
    {
        printf("Error 4: hash size isn't zero\n");
    }
     data  = HashFind(hash, &a);
  
  	puts("yuval id before adding is:");
    printf("%lu\n", ((person_t *)data)->idNum);

    data  = HashFind(hash, &b);
  
  	puts("amit id before adding is:");
    printf("%lu\n", ((person_t *)data)->idNum);

	data  = HashFind(hash, &c);
  
  	puts("maia id before adding is:");
    printf("%lu\n", ((person_t *)data)->idNum);
    data  = HashFind(hash, &d);
  
  	puts("adi id before adding is:");
    printf("%lu\n", ((person_t *)data)->idNum);

	HashForEach(hash, AddToID, &ten);

     data  = HashFind(hash, &a);
  
  	puts("yuval id after adding is:");
    printf("%lu\n", ((person_t *)data)->idNum);

    data  = HashFind(hash, &b);
  
  	puts("amit id after adding is:");
    printf("%lu\n", ((person_t *)data)->idNum);

	data  = HashFind(hash, &c);
  
  	puts("maia id after adding is:");
    printf("%lu\n", ((person_t *)data)->idNum);
    
    data  = HashFind(hash, &d);
  
  	puts("adi id after adding is:");
    printf("%lu\n", ((person_t *)data)->idNum);


 	HashDestroy(hash);
}