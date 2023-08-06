/*********************************
 * Reviewer:                
 * Author: Koby Touitou         
 * File: 100k_threads.c                 
 * ******************************/
#include <pthread.h> /* pthread_create, pthread_join */
#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */
#include <sys/resource.h> /* getrlimit */
#include <stdlib.h> /* malloc, free */

#define SIZE 12
#define NUM 1000000000


typedef struct calc_range
{
    size_t from;
    size_t to;
    size_t num;
}calc_range_t;

size_t SumArr(void *arr);
void PrtThreadsLimits();
int ThreadsTest(void);
void *SumOfDiv(void *calc);
int g_s[SIZE] = {0};


int main()
{
    size_t i = 0;
    int ret_val1 = 0;
    void *ret_val2[SIZE] = {0};
    pthread_t thread_id[SIZE] = {0};
    calc_range_t *new_calc = NULL;

    calc_range_t *calc_arr[SIZE] = {NULL};

    for(i = 0; i < SIZE; ++i)
    {
        new_calc = (calc_range_t *)malloc(sizeof(calc_range_t));
        new_calc->num = NUM;
        new_calc->from = i * (new_calc->num / SIZE);
        new_calc->to = (i + 1) * (new_calc->num / SIZE);

        calc_arr[i] = new_calc;
    }

    calc_arr[0]->from = 1;

    for(i = 0; i < SIZE; ++i)
    {
        if((ret_val1 = pthread_create(thread_id + i, NULL, SumOfDiv, calc_arr[i])))
        {
            return 1;
        }
    }

    for(i = 0; i < SIZE; ++i)
    {
        if((ret_val1 = pthread_join(thread_id[i], &ret_val2[i])))
        {
            return 1;
        }
        if ((ret_val2 + i) == PTHREAD_CANCELED)
        {
            printf("The thread was canceled\n");
        }
    }

    printf("Sum of divisor: %lu\n", SumArr(ret_val2));
    PrtThreadsLimits();

    return 0;
}

void *SumOfDiv(void *calc)
{
    size_t i = 0;
    calc_range_t *calc_range = (calc_range_t *)calc;
    size_t sum_of_divisor = 0;

    for(i = calc_range->from; i < calc_range->to; ++i)
    {
        if(!(calc_range->num % i))
        {
            sum_of_divisor += i;
        }
    }

    return (void *)sum_of_divisor;
}

int ThreadsTest(void)
{
    int i = 0;
    int test = 0;

    for(i = 0; i < SIZE; ++i)
    {
        test += g_s[i] != i;
    }
    
    return test;
}

void PrtThreadsLimits()
{
    struct rlimit newp;
    getrlimit(RLIMIT_NPROC, &newp);

    printf("Soft limit: %ld\nHard_limt: %ld\n", newp.rlim_cur, newp.rlim_max);
}

size_t SumArr(void *arr)
{
    size_t sum = 0;
    size_t i = 0;
    size_t *new_arr = NULL;
    
    new_arr = (size_t *)arr;

    for(i = 0; i < SIZE; ++i)
    {
        sum += new_arr[i];
    }

    return sum;
}

