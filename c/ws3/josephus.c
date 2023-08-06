#include <stdio.h> /* printf */
#include <stdlib.h> /* calloc */

int LastSoldier(int sldr_num) /* 0 is alive. 1 is dead */
{
    int *isDead = NULL;
    int search_alive = 0;
    int i = 0; /* variable for loop */
    
    isDead = (int *)calloc(sldr_num, sizeof(int));
    
    for (i = 0; i < sldr_num - 1; i++)
    {
        search_alive++;
        
        while (isDead[search_alive % sldr_num]==1)
        {
            search_alive++;
        }
        
        isDead[search_alive % sldr_num]=1;
        
        search_alive++;
        
        while (isDead[search_alive % sldr_num]==1)
        {
            search_alive++;
        }
    }
    
    free(isDead);
    isDead = NULL;
    
    return (search_alive % sldr_num);
}




int main()
{
    int num_soldiers = 8;
    int res =0;
    
    res = LastSoldier(num_soldiers);
   

    return 0;
}
