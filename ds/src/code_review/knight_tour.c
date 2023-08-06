/*********************************
 * Reviewer: Yisrael Fisch
 * Author: Avigail Millatiner
 * File: dhcp.c
 * ******************************/
#include <stdlib.h>/*malloc,free*/
#include <stdio.h> /*printf*/
#include <assert.h>

#include "knight_tour.h"
#include "bit_array.h"

#define N 8

int x_move[] = {+1, +2, -1, -2, -1, -2, +1, +2};
int y_move[] = {+2, +1, +2, +1, -2, -1, -2, -1};

typedef struct path
{
    int *path;
}path_t;

int RecursiveKnightTour(bit_array_t ba, path_t solution, position_t position);
int IsValidStep(position_t position, bit_array_t ba); 
size_t PtoBAPosition(position_t position);

position_t NextMove(position_t position, bit_array_t ba);
position_t BAtoPosition(size_t position);
int WaldorffsKnightTour(bit_array_t ba, path_t solution, position_t position);
int GetDegree(position_t position, bit_array_t ba);


void KnightTour(position_t position, int *path)
{
    bit_array_t ba = 0;
    path_t solution;
    size_t ba_position = 0;

    solution.path = path;
    ba_position = PtoBAPosition(position);
    ba = BitArraySetOn(ba,ba_position);
    solution.path[ba_position] = 1;
/*     RecursiveKnightTour(ba, solution, position);
 */
    if(0 != WaldorffsKnightTour(ba, solution, position))
    {
        printf("no solution\n");
    }
}

int RecursiveKnightTour(bit_array_t ba, path_t solution, position_t position)
{
    int i = 0;
    position_t next_position = {0};
    size_t ba_next_position = 0;

    if(N*N == BitArrayCountOn(ba))
    {
        return 0;
    }

    for(i=0; i<N; ++i)
    {
        next_position.x = position.x + x_move[i];/*אפשר להוציא לפונקציה שמוצאת את הצעד הבא*/
        next_position.y = position.y + y_move[i];
        if(IsValidStep(next_position,ba))
        {
            ba_next_position = PtoBAPosition(next_position);
            solution.path[ba_next_position] = BitArrayCountOn(ba)+1;
            ba = BitArraySetOn(ba,ba_next_position);
            if(0 == RecursiveKnightTour(ba, solution, next_position))
            {
                return 0;
            }
            ba = BitArraySetOff(ba,ba_next_position);/*אפשר להדליק רק את הביט הנוכחי ואז לא צריך לכבות במקרה שצריך לחזור אחורה*/
            solution.path[ba_next_position] = 0;/* אם היית  מכניסה כל פעם את הערך לאינדקס לפי מספר הצעד לא היית צריכה לאפס כי בפעם הבאה הערך היה נדרס */
        }
    }
    return 1;
}

int IsValidStep(position_t position, bit_array_t ba) 
{
    size_t ba_position = PtoBAPosition(position);
    return (position.x >= 0 && position.x < N && 
            position.y >= 0 && position.y < N && 
            1 != BitArrayGetVal(ba,ba_position));
}

size_t PtoBAPosition(position_t position)
{
    return position.x*N + position.y;
}

position_t BAtoPosition(size_t position)
{
    position_t res = {0,0};
    res.x = position/N;
    res.y = position%N;
    return res;
}


/*Warndorff's algorithm*/

int WaldorffsKnightTour(bit_array_t ba, path_t solution, position_t position)
{
    int i = 0;
    position_t false_position = {-1,-1};
    size_t ba_false_position = PtoBAPosition(false_position);
    size_t ba_position = 0;


    for (i = 0; i < N*N-1; ++i)
    {
        position = NextMove(position,ba);
        ba_position = PtoBAPosition(position);
        if(ba_false_position != ba_position)/*אין אפשרות שלא תמצאי שום צעד לכן התנאי מיותר*/
        {
            solution.path[ba_position] = BitArrayCountOn(ba)+1;
            ba = BitArraySetOn(ba,ba_position);
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

int GetDegree(position_t position, bit_array_t ba)
{
    int count = 0;
    int i = 0;
    position_t next_position = {0};


    for (i = 0; i < N; ++i)
    {
        next_position.x = position.x + x_move[i];
        next_position.y = position.y + y_move[i];
        if (IsValidStep(next_position, ba))
        {
            ++count;
        }
    }
    return count;
}

position_t NextMove(position_t position, bit_array_t ba)
{
    int min_degree_index = -1, degree = 0, min_degree = (N+1);
    position_t next_position = {0};
    int i = 0;

    for (i = 0; i < N; ++i)
    {
        next_position.x = position.x + x_move[i];
        next_position.y = position.y + y_move[i];
        degree = GetDegree(next_position, ba);
        if (1 == IsValidStep(next_position, ba) && (degree <= min_degree))
        {
            min_degree_index = i;
            min_degree = degree;
        }
    }
 
    if (min_degree_index == -1)/*אין אפשרות שלא תמצאי צעד אז התנאי מיותר.*/
    {
        next_position.x = -1;
        next_position.y = -1;   
        return next_position;     
    }
 
    next_position.x = position.x + x_move[min_degree_index];
    next_position.y = position.y + y_move[min_degree_index];
    return next_position;
}




