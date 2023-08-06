/*********************************
 * Reviewer: 				
 * Author: Yisrael Fisch			
 * File: knight_tour_test.c				
 * ******************************/

#include "knight_tour.h" 
static void PrtPath(int *path)
{
    int i = 0;
    puts("*****************************");
    for(i = 0; i < 64; ++i)
    {
        if(0 == i % 8)
        {
            printf("\n");
        }
        printf("%d\t", path[i]);
    }
    printf("\n");
}


int main()
{
    position_t first_pos = {3, 0};
    int path[64] = {0};
  
    KnightTour(first_pos, path);

    PrtPath(path);
   
    return 0;
}
