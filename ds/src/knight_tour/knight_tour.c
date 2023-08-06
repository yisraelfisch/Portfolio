/*********************************
 * Reviewer: 				
 * Author: Yisrael Fisch 			
 * File: knight_tour.c					
 * ******************************/
 
 /**/

#include <assert.h> /*assert*/
#include <stdio.h> /* printf */
#include "bit_array.h"
#include "knight_tour.h"
/*******Defines******/



/*******Structs******/
typedef struct
{
  position_t LUT[8];
} LUT_by_val;

/*******Service Funcs******/
/* Init the the LUT contained in a struct */
static LUT_by_val InitLUT()
{
    LUT_by_val LUT;

    LUT.LUT[0].x = 1;
    LUT.LUT[0].y = 2;

    LUT.LUT[1].x = 2;
    LUT.LUT[1].y = 1;

    LUT.LUT[2].x = 2;
    LUT.LUT[2].y = -1;

    LUT.LUT[3].x = 1;
    LUT.LUT[3].y = -2;

    LUT.LUT[4].x = -1;
    LUT.LUT[4].y = -2;

    LUT.LUT[5].x = -2;
    LUT.LUT[5].y = -1;

    LUT.LUT[6].x = -2;
    LUT.LUT[6].y = 1;

    LUT.LUT[7].x = -1;
    LUT.LUT[7].y = 2;

    return LUT;
}

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

/* Convert x and y to single index */
static int CalculatePos(int x, int y)
{
    return y * 8 + x;
}

/* Calculate and Validate the next position; return 0 for invalid position */
static int NextPosIsValid(position_t curr_pos, bit_array_t board)
{
    int next_pos = 0;
    
    next_pos = CalculatePos(curr_pos.x, curr_pos.y);
    
    return next_pos >= 0 && next_pos < 64 && !BitArrayGetVal(board, next_pos);
}

static position_t GetNextPos(position_t curr_pos, LUT_by_val LUT, int i)
{
    position_t next_pos = {0};
    
    next_pos.x = curr_pos.x + LUT.LUT[i].x;
    next_pos.y = curr_pos.y + LUT.LUT[i].y;
    
    return next_pos;
}


static int RecursiveKnightTour(position_t pos, LUT_by_val LUT, bit_array_t board, int *path)
{
    int i = 0;
    position_t next_pos = {0};

    *path = CalculatePos(pos.x, pos.y);
    board = BitArraySetOn(board, *path);
    
    if((long)board == -1)
    {
        return 1;
    }

    for(i = 0; i < 8; ++i)
    {
        next_pos = GetNextPos(pos, LUT, i);
        if(NextPosIsValid(next_pos, board)&&RecursiveKnightTour(next_pos, LUT, board, path + 1))
        {
            
            return 1;   
        
        }
    }

    return 0;
}

/**/
static int GetNumOfOptions(position_t pos, LUT_by_val LUT, bit_array_t board)
{
    int count = 0;
    size_t i = 0;

    for(i = 0; i < 8; ++i)
    {
        if(NextPosIsValid(GetNextPos(pos, LUT, i), board))
        {
            ++count;
        }
    }

    return count;
}


static position_t GetBestNextMove(position_t pos, LUT_by_val LUT, bit_array_t board)
{
    size_t i = 0;
    int min_options = 9;
    int num_of_options = 0;
    position_t next_pos = pos;
    position_t min_pos = pos;
    

    for(i = 0; i < 8; ++i)
    {
        if(NextPosIsValid(next_pos = GetNextPos(pos, LUT, i), board))
        {   
            num_of_options = GetNumOfOptions(next_pos, LUT, board);
            if(num_of_options < min_options )
            {
                min_options = num_of_options;
                min_pos = next_pos;
            }
        }
    }
    return min_pos;
}

static int KnightTourWarnsdorf(position_t pos, LUT_by_val LUT, bit_array_t board, int *path)
{
    position_t next_pos = {0};

     *path = CalculatePos(pos.x, pos.y);
    board = BitArraySetOn(board, *path);
    
    if((long)board == -1 )
    {
        return 1;
    }
    
    next_pos = GetBestNextMove(pos, LUT,board);
    return KnightTourWarnsdorf(next_pos, LUT, board, path + 1);
          
}

/*******Funcs Funcs******/

void KnightTour1(position_t position, int *path)
{
    LUT_by_val LUT;
    bit_array_t board = 0;
    assert(path);

    LUT = InitLUT();
    
    if(KnightTourWarnsdorf(position, LUT, board, path))
    {
        PrtPath(path);
    }
}

void KnightTour(position_t position, int *path)
{
    LUT_by_val LUT;
    bit_array_t board = 0;
    assert(path);

    LUT = InitLUT();
    
    if(RecursiveKnightTour(position, LUT, board, path))
    {
        PrtPath(path);
    }
}