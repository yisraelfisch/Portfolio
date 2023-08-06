#include <stdio.h>
#include <stdlib.h>

int *copy_an_array(int x, int array[]);

int main()
{
int arry[] = {1,2,3,4,5,6};
int size = 6, i;
int *arry2 = copy_an_array(size, arry);


    for(i = 0; i < size; i++)
    {
    printf("%d", arry2[i]);
    }

free(arry2);
return 0;
}

int *copy_an_array(int x, int array[])
{
int i;
int *copy;
copy = (int*)malloc(x * sizeof(int));

    if(copy == NULL)
    {
    printf("no memory allocated");
    exit(0);
    }
    
    for(i = 0; i < x; i++)
    {
    copy[i] = array[i];
    }
return copy;  

}  
