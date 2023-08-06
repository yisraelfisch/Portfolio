#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "dll.h"

#define THREADS 10
void *prod(void *param);
void *cons(void *param);
void HandleTask(void *param);
pthread_mutex_t lock = {0};

dll_t *dlist = NULL;
int prod_counter = 0;
int cons_counter = 0;
int shut_down = 0;

int main()
{
    size_t i = 0;
    pthread_t thread_prod[THREADS] = {0};
    pthread_t thread_cons[THREADS] = {0};
    void *thread_ret_val_prod[THREADS] = {(void *)1};
    void *thread_ret_val_cons[THREADS] = {(void *)1};

    if(!(dlist = DListCreate()))
    {
        perror("DListCreate");
        return 1;
    }

    for(i = 1; i <= THREADS; i++)
    {
        if(pthread_create(thread_cons + i, NULL, cons, NULL))
        {
            perror("pthread_create");
            return 1;
        }
    }

    for(i = 1; i <= THREADS; i++)
    {
        if(pthread_create(thread_prod + i, NULL, prod, (void *)i))
        {
            perror("pthread_create");
            return 1;
        }
    }

    sleep(5);
    shut_down = 1;

    for(i = 1; i <= THREADS; i++)
    {
        if(pthread_join(thread_prod[i], &thread_ret_val_prod[i]))
        {
            perror("pthread_join");
            return 1;
        }
    }

    for(i = 0; i < THREADS; i++)
    {
        DListPushBack(dlist, (void *)770);
    }

    for(i = 1; i <= THREADS; i++)
    {
        if(pthread_join(thread_cons[i], &thread_ret_val_cons[i]))
        {
            perror("pthread_join");
            return 1;
        }
    }

    for(i = 1; i <= THREADS; ++i)
    {
        if(thread_ret_val_prod[i] || thread_ret_val_cons[i])
        {
            puts("Error");
        }
    }

    if(cons_counter != prod_counter)
    {
        printf("cons: %d\n", cons_counter);
        printf("prod: %d\n", prod_counter);
        puts("Error");
    }
    pthread_mutex_destroy(&lock);
    DListDestroy(dlist);
    return 0;
}

void *cons(void *param)
{
    size_t task = 0;
   
    (void)(param);

    while(1)
    {
        
        while(DListIsEmpty(dlist));
        pthread_mutex_lock(&lock);
        
        if(DListIsEmpty(dlist))
        {
            pthread_mutex_unlock(&lock);
            continue;    
        }

        if(!DListIsEmpty(dlist))
        {
            if((task = (size_t)DListPopFront(dlist)) == 770)
            {
                pthread_mutex_unlock(&lock);
                break;
            }
            else
            {
                ++cons_counter;
            }
        }
                
        pthread_mutex_unlock(&lock);
    
        HandleTask((void *)task);
        
    }

    return NULL;
}

void *prod(void *param)
{
   
    while(1)
    {
        usleep(500);
        
        pthread_mutex_lock(&lock);
        if(DListIsSameIter(DListPushBack(dlist, param), DListEnd(dlist)))
        {
            perror("prod");
            return NULL;
        }
        ++prod_counter;
        pthread_mutex_unlock(&lock);
        if(shut_down)
        {
            break;
        }
    }

    return NULL;
}

void HandleTask(void *param)
{
    printf("%ld\n", (size_t)param);
}

