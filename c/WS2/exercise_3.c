#include <stdio.h>
#include <stdlib.h>
static int s_i = 7;

int main ()
{
    int i = 7;
    int *ptr = &i;
    int *ptr2 = (int*)malloc(sizeof(int));
    
     printf("Address of s_i: %p\n", (void *)&s_i);
    printf("Address of i: %p\n", (void *)ptr);
    printf("Address of ptr: %p\n", (void *)&ptr);
    printf("Address of ptr2: %p\n", (void *)&ptr2);
    
    if(ptr)
    {
        int **ptr3 = &ptr;
        printf("Address of ptr3: %p\n", (void *)&ptr3);

    }

    
   
    
    free(ptr2);
    return 0;
}    
