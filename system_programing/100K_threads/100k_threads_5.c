/*********************************
 * Reviewer:                
 * Author: Koby Touitou         
 * File: 100k_threads.c                 
 * ******************************/
#include <pthread.h> /* pthread_create */
#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */
#include <sys/resource.h> /* getrlimit */
#include <stdlib.h> /* malloc, free */

#define NUM 1000000000

size_t SumOfDiv(size_t calc);

int main()
{
    printf("Sum of divisor: %lu\n", SumOfDiv(NUM));
    return 0;
}

size_t SumOfDiv(size_t calc)
{
    size_t i = 0;
    size_t sum_of_divisor = 0;

    for(i = 1; i < calc; ++i)
    {
        if(!(calc % i))
        {
            sum_of_divisor += i;
        }
    }

    return sum_of_divisor;
}

