/*********************************
 * Reviewer: Yisrael Fisch
 * Author: Roy Mantel
 * File Name: avl_test.c
 * ******************************/

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc free */
#include <string.h>	/* strcpy */
#include "avl.h"

typedef struct person
{
    size_t ID;
    char name[50];
} person_t;

static person_t PersonInit(size_t ID, char *name)
{
    person_t person = {0};
    person.ID = ID;
    strcpy(person.name, name);

    return person;
}

int PersonCompare(const void *person1, const void *person2, void* param)
{
    *(size_t *)param += 1;
    return *(size_t *)person2 - *(size_t *)person1;
}

int MultiplyPersonID(void *data, void *param)
{
	person_t *st = (person_t *)data;
	st->ID *= *(size_t *)param;
	return 0;
}

void TestCreateInsert(void);
void TestRemove(void);
void TestForEach(void);

int IntsCompare(const void *num1, const void *num2, void *param)
{
	*(size_t *)param += 1;
    return *(int *)num2 - *(int *)num1;
}

int main(void)
{
	TestCreateInsert();
	TestRemove();
	TestForEach();

	return 0;
}

void TestCreateInsert(void)
{
	avl_t *avl = NULL;
	int num1 = 42, num2 = 13, num3 = 7, num4 = 99;
	int num_find = 0;
	size_t counter = 0;

	avl = AvlCreate(IntsCompare, &counter);
	if(!avl)
	{
		printf("(╥﹏╥) Error: AvlCreate returned NULL on Line %d\n", __LINE__);
	}

	if(0 != AvlInsert(avl, &num1))
	{
		printf("(╥﹏╥) Error: AvlInsert failed on Line %d\n", __LINE__);
	}
	
	if(0 != AvlInsert(avl, &num2))
	{
		printf("(╥﹏╥) Error: AvlInsert failed on Line %d\n", __LINE__);
	}

	if(0 != AvlInsert(avl, &num3))
	{
		printf("(╥﹏╥) Error: AvlInsert failed on Line %d\n", __LINE__);
	}

	if(3 != AvlSize(avl))
	{
		printf("(╥﹏╥) Error: AvlSize failed on Line %d\n", __LINE__);
		printf("Expected 3 got %ld\n", AvlSize(avl));
	}

	if(0 != AvlInsert(avl, &num4))
	{
		printf("(╥﹏╥) Error: AvlInsert failed on Line %d\n", __LINE__);
	}
	
	if(7 != (num_find = *(int *)AvlFind(avl, &num3)))
	{
		printf("(╥﹏╥) Error: AvlFind failed on Line %d\n", __LINE__);
	}

	if(4 != AvlSize(avl))
	{
		printf("(╥﹏╥) Error: AvlSize failed on Line %d\n", __LINE__);
		printf("Expected 4 got %ld\n", AvlSize(avl));
	}

	if(2 != AvlHeight(avl))
	{
		printf("(╥﹏╥) Error: AvlHeight failed on Line %d\n", __LINE__);
		printf("Expected 2 got %ld\n", AvlHeight(avl));
	}

	AvlDestroy(avl);
}

void TestRemove(void)
{
	avl_t *avl = NULL;
	int num1 = 42, num2 = 13, num3 = 7, num4 = 99, num5 = 33, num6 = 71;
	int *num_find = NULL;
	size_t counter = 0;

	avl = AvlCreate(IntsCompare, &counter);

	AvlInsert(avl, &num1);
	AvlInsert(avl, &num2);
	AvlInsert(avl, &num3);
	AvlInsert(avl, &num4);
	AvlInsert(avl, &num5);
	AvlInsert(avl, &num6);

	AvlRemove(avl, &num5);
	if(NULL != (num_find = (int *)AvlFind(avl, &num5)))
	{
		printf("(╥﹏╥) Error: removed leaf found in tree on line %d\n", __LINE__);
	}

	AvlRemove(avl, &num4);
	if(NULL != (num_find = (int *)AvlFind(avl, &num5)))
	{
		printf("(╥﹏╥) Error: removed one child found in tree on line %d\n", __LINE__);
	}

	AvlRemove(avl, &num1);
	if(NULL != (num_find = (int *)AvlFind(avl, &num1)))
	{
		printf("(╥﹏╥) Error: removed two-child found in tree on line %d\n", __LINE__);
	}

	if(AvlIsEmpty(avl))
	{
		printf("(╥﹏╥) Error: suddenly the tree is empty %d\n", __LINE__);
	}
	
	AvlDestroy(avl);
}

void TestForEach(void)
{
	avl_t *avl = NULL;
	size_t counter = 0;
	person_t *p1 = NULL, *p2 = NULL, *p3 = NULL, *p4 = NULL, *p5 = NULL,
			*p6 = NULL, *p7 = NULL, *p8 = NULL, *p9 = NULL, *p10 = NULL;
	person_t p_find = {0}, p_found = {0};
	int res = 0, multiplier = 2;

	avl = AvlCreate(PersonCompare, &counter);

	p1 = (person_t *)malloc(sizeof(person_t));
	if(!p1)
	{
		printf("(╯°□°）╯︵ ┻━┻\tBad Malloc line %d\n", __LINE__);
		return;
	}
	*p1 = PersonInit(5, "David");

	p2 = (person_t *)malloc(sizeof(person_t));
	if(!p2)
	{
		printf("(╯°□°）╯︵ ┻━┻\tBad Malloc line %d\n", __LINE__);
		return;
	}
	*p2 = PersonInit(18, "Yaffa");

	p3 = (person_t *)malloc(sizeof(person_t));
	if(!p3)
	{
		printf("(╯°□°）╯︵ ┻━┻\tBad Malloc line %d\n", __LINE__);
		return;
	}
	*p3 = PersonInit(30, "Omer");

	p4 = (person_t *)malloc(sizeof(person_t));
	if(!p4)
	{
		printf("(╯°□°）╯︵ ┻━┻\tBad Malloc line %d\n", __LINE__);
		return;
	}
	*p4 = PersonInit(52, "Guy");

	p5 = (person_t *)malloc(sizeof(person_t));
	if(!p5)
	{
		printf("(╯°□°）╯︵ ┻━┻\tBad Malloc line %d\n", __LINE__);
		return;
	}
	*p5 = PersonInit(12, "Rotem");

	p6 = (person_t *)malloc(sizeof(person_t));
	if(!p6)
	{
		printf("(╯°□°）╯︵ ┻━┻\tBad Malloc line %d\n", __LINE__);
		return;
	}
	*p6 = PersonInit(222, "Amit");


	p7 = (person_t *)malloc(sizeof(person_t));
	if(!p7)
	{
		printf("(╯°□°）╯︵ ┻━┻\tBad Malloc line %d\n", __LINE__);
		return;
	}
	*p7 = PersonInit(89, "Izevel");

	p8 = (person_t *)malloc(sizeof(person_t));
	if(!p8)
	{
		printf("(╯°□°）╯︵ ┻━┻\tBad Malloc line %d\n", __LINE__);
		return;
	}
	*p8 = PersonInit(747, "Snow-white");

	p9 = (person_t *)malloc(sizeof(person_t));
	if(!p9)
	{
		printf("(╯°□°）╯︵ ┻━┻\tBad Malloc line %d\n", __LINE__);
		return;
	}
	*p9 = PersonInit(11, "Donald");

	p10 = (person_t *)malloc(sizeof(person_t));
	if(!p10)
	{
		printf("(╯°□°）╯︵ ┻━┻\tBad Malloc line %d\n", __LINE__);
		return;
	}
	*p10 = PersonInit(527, "Ariel");

	AvlInsert(avl, p1);
	AvlInsert(avl, p2);
	AvlInsert(avl, p3);
	AvlInsert(avl, p4);
	AvlInsert(avl, p5);
	AvlInsert(avl, p6);
	AvlInsert(avl, p7);
	AvlInsert(avl, p8);
	AvlInsert(avl, p9);
	AvlInsert(avl, p10);

	res = AvlForEach(avl, MultiplyPersonID, (void *)&multiplier);
	if(0 != res)
	{
		printf("(╥﹏╥) Error: ForEach NoGood Line: %d\n", __LINE__);
	}

	p_find = PersonInit(104, "Guy");
	p_found = *(person_t *)AvlFind(avl, &p_find);

	if(p_found.ID != p4->ID)
	{
		printf("(╥﹏╥) Error: Find no work after ForEach line: %d\n", __LINE__);
	}

	free(p1);
	free(p2);
	free(p3);
	free(p4);
	free(p5);
	free(p6);
	free(p7);
	free(p8);
	free(p9);
	free(p10);
	p1 = p2 = p3 = p4 = p5 = p6 = p7 = p8 = p9 = p10 = NULL;
	
	AvlDestroy(avl);
}