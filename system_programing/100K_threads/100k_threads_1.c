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
    pthread_t thread_id = 0;
    size_t i = 0;

   for(i = 0; i < SIZE; ++i)
    {
        pthread_create(&thread_id, NULL, InsertVal, (void *)i);
    }

    sleep(10);
    
    printf("%s\n", ThreadsTest() ? "FAILED" : "SUCCSESS");

    return 0;
}

void *InsertVal(void *i)
{
    g_s[(size_t)i] = (size_t)i;
    
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

