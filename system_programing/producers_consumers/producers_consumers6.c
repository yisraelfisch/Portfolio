#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>

#define PROD_THREADS 1
#define CONS_THREADS 4

void *prod(void *param);
void *cons(void *param);
void HandleTask(size_t param);

pthread_mutex_t lock = {0};
sem_t ready_to_consume_data = {0};
pthread_cond_t data_produced = {0};

int shut_down = 1;
size_t msg = 0;
size_t poisen_apple = 999999999;

int main()
{
    size_t i = 0;
    pthread_t thread_prod[PROD_THREADS] = {0};
    pthread_t thread_cons[CONS_THREADS] = {0};
    void *thread_ret_val_prod[PROD_THREADS] = {(void *)1};
    void *thread_ret_val_cons[CONS_THREADS] = {(void *)1};

    if(sem_init(&ready_to_consume_data, 0, 0))
    {
        perror("sem_init");
        return 1;
    }

    if(pthread_mutex_init(&lock, NULL))
    {
        perror("pthread_mutex_init");
        return 1;
    }

    if(pthread_cond_init(&data_produced, NULL))
    {
        perror("pthread_cond_init");
        return 1;
    }

    for(i = 1; i <= PROD_THREADS; ++i)
    {
        if(pthread_create(thread_prod + i - 1, NULL, prod, NULL))
        {
            perror("pthread_create");
            return 1;
        }
    }

    for(i = 1; i <= CONS_THREADS; ++i)
    {
        if(pthread_create(thread_cons + i - 1, NULL, cons, NULL))
        {
            perror("pthread_create");
            return 1;
        }
    }

    sleep(10);
    shut_down = 0;

    for(i = 1; i <= PROD_THREADS; ++i)
    {
        if(pthread_join(thread_prod[i - 1], &thread_ret_val_prod[i - 1]))
        {
            perror("pthread_join");
            return 1;
        }
    }

    for(i = 0; i < CONS_THREADS; ++i)
    {
        sem_wait(&ready_to_consume_data);
    }

    pthread_mutex_lock(&lock);
    msg = poisen_apple;
    pthread_mutex_unlock(&lock);
    pthread_cond_broadcast(&data_produced);

    for(i = 1; i <= CONS_THREADS; i++)
    {
        if(pthread_join(thread_cons[i - 1], &thread_ret_val_cons[i - 1]))
        {
            perror("pthread_join");
            return 1;
        }
    }

    for(i = 1; i <= CONS_THREADS; ++i)
    {
        if(thread_ret_val_cons[i - 1])
        {
            puts("Error");
        }
    }

    if(sem_destroy(&ready_to_consume_data) || pthread_cond_destroy(&data_produced) || pthread_mutex_destroy(&lock)) 
    {
        perror ("destroy");
        return 1;
    }

    return 0;
}



void *cons(void *param)
{
    size_t handle = 0;
    (void)param;

    while(1)
    {
        pthread_mutex_lock(&lock);
        sem_post(&ready_to_consume_data);
        pthread_cond_wait(&data_produced, &lock);
        handle = msg;
        pthread_mutex_unlock(&lock);
        
        if(handle == poisen_apple)
        {
            break;
        }

        HandleTask(handle);
    }

    return NULL;
}

void *prod(void *param)
{
    int i = 0;
    size_t j = 0;
    (void)param;

    while(shut_down)
    { 
        for(i = 0; i < CONS_THREADS; ++i)
        {
            sem_wait(&ready_to_consume_data);
        }
        
        pthread_mutex_lock(&lock);
        msg = ++j;
        pthread_mutex_unlock(&lock);

        pthread_cond_broadcast(&data_produced);
    }

    return NULL;
}

void HandleTask(size_t param)
{
    printf("%ld\n", param);
}
