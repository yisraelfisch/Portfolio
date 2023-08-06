/*************************************** 
file name: struct.c
Author: yisrael fisch.
*reviewer: avigail.
******************************************/
#include <stdio.h>/*printf, size_t*/
#include <string.h>/*strlen, sizeof*/
#include <stdlib.h>/*malloc, realloc, free*/

#define MAX2(a,b) ((a) > (b) ? (a) : (b))
#define MAX3(a,b,c) ((MAX2(a,b)) > (c) ? (MAX2(a,b)) : (c))
#define SIZEOF_VAR(var) ((size_t)(&(var)+1)-(size_t)(&(var)))
#define SIZEOF_TYPE(x) ((size_t)(1+((x *)0)))

typedef struct elements_types
{
	void *value_p;
	void (*AddFunc)(struct elements_types *element, int num_add);
	void (*PrintFunc)(struct elements_types const *element);
	void (*FreeFunc)(struct elements_types *element);
} element_t;			

/* int type */
void InitElementInt(element_t *element, int value);

void AddInt(element_t *element, int num_add);
void PrintInt(element_t const *element);
void FreeInt(element_t *element);

/* float type */
void InitElementFloat(element_t *element, float value);

void AddFloat(element_t *element, int num_add);
void PrintFloat(element_t const *element);
void FreeFloat(element_t *element);

/* str type */
void InitElementStr(element_t *element, const char *str);

void AddStr(element_t *element, int num_add);
void PrintStr(element_t const *element);
void FreeStr(element_t *element);
size_t GetNumDigits(int num_add);

void PrintElements(element_t *arr, size_t size);
void AddElements(element_t *arr, size_t size, int num);
void FreeElements(element_t *arr, size_t size);


int main ()
{
	int a = 1;
	int b = 2;
	int c = 3;
	element_t arr[3];
	printf("max 2 is: %d\n", MAX2(a,b));
	printf("max 3 is: %d\n", MAX3(a,b,c));
	printf("sizof var is: %ld\n", SIZEOF_VAR(a));
	printf("sizof type is: %ld\n", SIZEOF_TYPE(long));
    InitElementInt(arr , 2);
    InitElementFloat(arr + 1 ,15.5);
    InitElementStr(arr + 2, "israel");
    PrintElements(arr, 3);
    AddElements(arr, 3, 10);
    PrintElements(arr, 3);
	FreeElements(arr, 3);

	return 0;

} 

void InitElementInt(element_t *element, int value)
{

	element->value_p = (void *)(long)value;

	element->PrintFunc = PrintInt;
	element->AddFunc = AddInt;
	element->FreeFunc = FreeInt;
}

void AddInt(element_t *element, int num_add)
{
	element->value_p = (void*)((long)element->value_p + num_add);
}

void PrintInt(element_t const *element)
{
		printf("%ld", (long)element->value_p);
}

void FreeInt(element_t *element)
{
	element->value_p = NULL;
}


void InitElementFloat(element_t *element, float value)
{

	double val_2_double = (double)value;
	element->value_p = (void *)*((long *)&val_2_double);

	element->PrintFunc = PrintFloat;
	element->AddFunc = AddFloat;
	element->FreeFunc = FreeFloat;
}

void PrintFloat(element_t const *element)
{
	printf("%f", (float)*((double *)&element->value_p));
}

void AddFloat(element_t *element, int num_add)
{
    double new_val = *((double *)&element->value_p) + (double)num_add;
        
    element->value_p = (void *)*((long *)&new_val);
}

void FreeFloat(element_t *element)
{
	element->value_p = NULL;
}


void InitElementStr(element_t *element, const char *str)
{
	element->value_p = malloc((strlen(str) + 1) * sizeof(char));
	
	if (!element->value_p)
	{
		printf("string allocation failed");
		return;
	}
	
	strcpy((char *)element->value_p, str);
	element->PrintFunc = PrintStr;
	element->AddFunc = AddStr;
	element->FreeFunc = FreeStr;
}

void PrintStr(element_t const *element)
{
	printf("%s", (char *)element->value_p);	
}

void AddStr(element_t *element, int num_add)
{
	size_t num_add_len = GetNumDigits(num_add);
	size_t element_len = strlen(element->value_p);
	size_t overall_len = num_add_len + element_len + 1;
	
	element->value_p = realloc(element->value_p, sizeof(char) * overall_len);
	
	if (NULL == element->value_p)
	{
		printf("allocation unsuccessful\n");
		return;
	}
	
	sprintf(element->value_p, "%s%d", (char *)element->value_p, num_add);
}

void FreeStr(element_t *element)
{
	free(element -> value_p);
	element -> value_p = NULL;
}

size_t GetNumDigits(int num_add)
{
	size_t counter = 0;
	
	if (0 == num_add)
	{
		return 1;
	}
	
	while (num_add)
	{
		num_add /= 10;
		counter++;
	}
	
	return counter;
}

void PrintElements(element_t *arr, size_t size)
{		
	size_t i = 0;
	
	for(i = 0; i < size; i++)
	{
    		arr[i].PrintFunc(arr + i);
    		printf(", ");
    }
  
	/*arr[i].PrintFunc(arr + i);*/
	printf("\n");
    
}

void AddElements(element_t *arr, size_t size, int num)
{		
	size_t i = 0;
	
	for(i = 0; i < size; i++)
	{
    		arr[i].AddFunc(arr + i, num);
	}
}

void FreeElements(element_t *arr, size_t size)
{		
	size_t i = 0;
	
	for(i = 0; i < size; i++)
	{
	    	arr[i].FreeFunc(arr + i);
	}
}