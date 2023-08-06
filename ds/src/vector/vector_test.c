#include <stdio.h>/*printf*/
#include "vector.h"

/*functios to check succes*/
void CheckInt();
void CheckFloat();

int main()
{
	CheckInt();
	CheckFloat();
	return 0;

}

void CheckInt()
{
    vector_t *v = VectorCreate(3, sizeof(int));
    int *p;
    int x = 3;
    int y = 4;
    printf("*****\nint chek\n");
    printf("capacity after craeting is: %ld\n", VectorCapacity(v));
    printf("size after creating %ld\n", VectorSize(v));
    VectorPush(v, &x);
    p = (int *)VectorGetAccess(v, 0);
    printf("the number stored in index 0 is: %d\n", (*p));
    printf("size after pushing %ld\n", VectorSize(v));
    VectorShrinkToFit(v);
    printf("capacity after shrinking is: %ld\n", VectorCapacity(v));
    VectorReserve(v, 2);
    printf("capacity after reserve is: %ld\n", VectorCapacity(v));
    VectorPush(v, &y);
    p = (int *)VectorGetAccess(v, 1);
    printf("the number stored in index 1 is: %d\n", (*p));
    printf("size after pushing %ld\n", VectorSize(v));
    VectorPop(v);
    printf("size after poping %ld\n", VectorSize(v));
    printf("capacity is %ld\n",VectorCapacity(v));
    printf("empty check %d\n", (!VectorIsEmpty(v)));
    VectorDestroy(v);
}

void CheckFloat()
{
    vector_t *v = VectorCreate(3, sizeof(float));
    float *p;
    float x = 3;
    printf("*****\nfloat chek\n");
    printf("capacity after craeting is: %ld\n", VectorCapacity(v));
    printf("size after creating %ld\n", VectorSize(v));
    VectorPush(v, &x);
    p = (float *)VectorGetAccess(v, 0);
    printf("the number stored in index 0 is: %f\n", (*p));
    printf("size after pushing %ld\n", VectorSize(v));
    VectorShrinkToFit(v);
    printf("capacity after shrinking is: %ld\n", VectorCapacity(v));
    VectorPop(v);
    printf("size after poping %ld\n", VectorSize(v));
    printf("capacity is %ld\n",VectorCapacity(v));
    printf("empty check %d\n", (!VectorIsEmpty(v)));
    VectorDestroy(v);
}