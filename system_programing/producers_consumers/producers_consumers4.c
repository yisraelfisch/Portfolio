#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>
#include "circular_buffer.h"

#define THREADS 10
#define SIZE 10
void *prod(void *param);
void *cons(void *param);
void HandleTask(size_t param);
pthread_mutex_t lock = {0};
sem_t sem_prod = {0};
sem_t sem_cons = {0};

circ_buff_t *c_buff = NULL;
size_t poisen_apple = 770;
int cons_prod_counter = 0;
int shut_down = 0;

int main()
{
    size_t i = 0;
    pthread_t thread_prod[THREADS] = {0};
    pthread_t thread_cons[THREADS] = {0};
    void *thread_ret_val_prod[THREADS] = {(void *)1};
    void *thread_ret_val_cons[THREADS] = {(void *)1};
    size_t buffer[SIZE] = {0};

    if(sem_init(&sem_prod, 0, SIZE) || sem_init(&sem_cons, 0, 0))
    {
        perror("sem_init");
        return 1;
    }

    if(!(c_buff = CircBuffCreate(SIZE * sizeof(size_t))))
    {
        perror("CircBuffCreate");
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
        buffer[i - 1] = i;
        if(pthread_create(thread_prod + i, NULL, prod, buffer + i - 1))
        {
            perror("pthread_create");
            return 1;
        }
    }

    sleep(10);
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
        if(sem_wait(&sem_prod))
        {
            perror("sem_post");
            return 1;
        }

        if(CircBuffWrite(c_buff, &poisen_apple, sizeof(size_t)) != sizeof(size_t))
        {
            perror("CircBuffWrite");
            return 1;
        }
        
        if(sem_post(&sem_cons))
        {
            perror("sem_post");
            return 1;
        }
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

    if(cons_prod_counter)
    {
        puts("Error");
    }

    if(sem_destroy(&sem_prod) || sem_destroy(&sem_cons)) 
    {
        perror ("sem_destroy");
        return 1;
    }

    pthread_mutex_destroy(&lock);
    CircBuffDestroy(c_buff);

    return 0;
}

void *cons(void *param)
{
    size_t task = 0;
    (void)(param);

    while(1)
    {        
        if(sem_wait(&sem_cons))
        {
            perror ("sem_wait");
            return NULL;
        }
        
        pthread_mutex_lock(&lock);
        if(CircBuffIsEmpty(c_buff))
        {   
            pthread_mutex_unlock(&lock);
            continue;
        }

        if((CircBuffRead(c_buff, &task, sizeof(size_t)) != sizeof(size_t)))
        {
            perror("CircBuffRead");
            return NULL;
        }
        
        if(task == 770)
        {
            pthread_mutex_unlock(&lock);
            if(sem_post(&sem_prod))
            {
                perror ("sem_wait");
                return NULL;
            }

            break;
        }
        else
        {
            --cons_prod_counter;
        }
        pthread_mutex_unlock(&lock);
        
        if(sem_post(&sem_prod))
        {
            perror ("sem_wait");
            return NULL;
        }

        HandleTask(task);
    }

    return NULL;
}

void *prod(void *param)
{
    while(1)
    {
        usleep(rand() % 1000);
        
        if(sem_wait(&sem_prod))
        {
            perror("sem_post");
            return NULL;
        }
        
        pthread_mutex_lock(&lock);
        if(CircBuffWrite(c_buff, param, sizeof(size_t)) != sizeof(size_t))
        {
            perror("prod");
            return NULL;
        }
        ++cons_prod_counter;

        pthread_mutex_unlock(&lock);
        
        if(sem_post(&sem_cons))
        {
            perror("sem_post");
            return NULL;
        }
        
        if(shut_down)
        {
            break;
        }
    }

    return NULL;
}

void HandleTask(size_t param)
{
    printf("%ld\n", param);
}