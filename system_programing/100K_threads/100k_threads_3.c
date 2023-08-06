/*********************************
 * Reviewer:                
 * Author: Koby Touitou         
 * File: 100k_threads.c                 
 * ******************************/
#include <pthread.h> /* pthread_create */
#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */

#define SIZE 100000

int ThreadsTest(void);
void *InsertVal(void *i);
int g_s[SIZE] = {0};


int main()
{
    int ret_val = 1;
    pthread_t thread_id = 0;
    size_t i = 0;

   for(i = 0; i < SIZE; ++i)
    {
        while((ret_val = pthread_create(&thread_id, NULL, InsertVal, (void *)i)));
        ret_val = 1;
    }

    sleep(10);
    
    printf("%s\n", ThreadsTest() ? "FAILED" : "SUCCSESS");

    return 0;
}

void *InsertVal(void *i)
{
    g_s[(size_t)i] = (size_t)i;
    pthread_detach(pthread_self());
    
    return "Fuck it";
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
