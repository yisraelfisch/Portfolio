#include <stdio.h>

void swap_two_ints(int *ptr1, int *ptr2);

int main ()
{
    int x = 3;
    int y = 5;
    
    int *ptrx = &x;
    int *ptry = &y;
    swap_two_ints(ptrx, ptry);
    printf("x=%d\ny=%d", x, y);
    
    return 0;
}
    
void swap_two_ints(int *ptr1, int *ptr2)
{
    int temp = 0;
    
    temp = *ptr1;
    
    *ptr1 = *ptr2;
    
    *ptr2 = temp;
    
    
}
