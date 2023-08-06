/*********************************
 * Reviewer: 				
 * Author: Yisrael Fisch			
 * File: knight_tour_test.c				
 * ******************************/

#include "knight_tour.h" 

int main()
{
    position_t first_pos = {0, 0};
    int path[64] = {0};
  
    KnightTour(first_pos, path);
    KnightTour1(first_pos, path);
    return 0;
}
