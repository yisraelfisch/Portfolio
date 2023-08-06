#include <stdio.h>
#include <stddef.h>
void SwapTwoSize_t(size_t *ptr1, size_t *ptr2);

int main ()
{
    size_t x = 3;
    size_t y = 5;
    
    size_t *ptrx = &x;
    size_t *ptry = &y;
    
    
    
    printf("before swap x=%lu\ny=%lu", x, y);
    
    SwapTwoSize_t(ptrx, ptry);
    printf("after swap x=%lu\ny=%lu", x, y);
    
    return 0;
}
    
void SwapTwoSize_t(size_t *ptr1, size_t *ptr2)
{
   
    size_t temp = *ptr1;
    
    *ptr1 = *ptr2;
    
    *ptr2 = temp;
    
    
}
