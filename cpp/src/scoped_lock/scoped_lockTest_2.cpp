#include <pthread.h>
#include <cstdio>
#include <semaphore.h>
#include "scoped_lock_2.hpp"

using namespace ilrd;



/*------------global-variable-------------*/

/* pthread_mutex_t posix;
pthread mutex_1(posix); */

spin_lock mutex_2;

int g_index = 0;
sem_t sem = {0};

void* producer(void* arg);
void* consumer(void* arg);
void handle_task(int data);


int main()
{
    int i = 0;
    int buf[10] = {0};
    pthread_t prod = 0;
    pthread_t cons[10] = {0};


    
    if(sem_init(&sem, 0, 0))
    {
        perror("sem_init");
        return 1;
    }

    if(pthread_create(&prod, NULL, producer, buf))
    {
        perror("pthread_create");
        return 1;
    }

    for(i = 0; i < 10; ++i)
    {
        if(pthread_create(cons + i, NULL, consumer, buf))
        {
            perror("pthread_create");
        }
    }

    if(pthread_join(prod, NULL))
    {
        perror("pthread_join");
        return 1;
    }

    for(i = 0; i < 10; ++i)
    {
        if(pthread_join(cons[i], NULL))
        {
            perror("pthread_join");
            return 1;
        }
    }

    if(sem_destroy(&sem))
    {
        perror("sem_destroy");
        return 1;
    }

    return 0;
}

void* producer(void* arg)
{
    int i = 0;
    for(i = 0; i < 10; ++i)
    {
        ((int *)arg)[i] = i + 1;
        sem_post(&sem);
    }

    return NULL;
}

void* consumer(void* arg)
{
   
    /* ScopedLock <pthread>lock(mutex_1, true); */
    ScopedLock <spin_lock>lock(mutex_2, true);

    int temp = 0;
    sem_wait(&sem);
    
    /* while(lock);
    lock.Lock(); */
    while(!lock)
    {
        lock.Lock();
    }
    
    if(((int *)arg)[g_index])
    {
        temp = ((int *)arg)[g_index];
    }

    puts("New consumed value");

    ++g_index;
    lock.Unlock();
    


    if(temp)
    {
        handle_task(temp);
    }

    return NULL;
}

void handle_task(int data)
{
    printf("%d\n", data);
}



