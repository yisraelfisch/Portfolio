/*********************************
 * Reviewer: 
 * Author: yisrael fisch
 * File: BtsQueue.cpp
 * ******************************/

#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include "BtsQueue.hpp"

//uncomment #define TEST in BtsQueue.hpp inorder to see what happens when you don't lock
using namespace std;
using namespace ilrd;
BtsQueue <int>queue_int;

void* producer(void* arg);
void* consumer(void* arg);

int main()
{
    const int NUMBER = 10;
    int i = 0;
    pthread_t prod_thred [NUMBER]= {0};
    pthread_t cons_thred[NUMBER] = {0};

    int prod[NUMBER] = {1,2,3,4,5,6,7,8,9,10};
    int cons[NUMBER] = {0};

    
    for(i = 0; i < NUMBER; ++i)
    {
        if(pthread_create(prod_thred + i, NULL, producer, &prod[i]))
        {
            perror("pthread_create");
        }
    }

   

    for(i = 0; i < NUMBER; ++i)
    {
        if(pthread_create(cons_thred + i, NULL, consumer, &cons[i]))
        {
            perror("pthread_create");
        }
    }

    for(i = 0; i < NUMBER; ++i)
    {
        if(pthread_join(prod_thred[i], NULL)!=0)
        {
            perror("pthread_join");
            return 1; 
        }
    }
    for(i = 0; i < NUMBER; ++i)
    {
        if(pthread_join(cons_thred[i], NULL)!=0)
        {
            perror("pthread_join");
            return 1; 
        }
    }

    for(i = 0; i < NUMBER; ++i)
    {
        cout << cons[i]  << endl;

    }

    return 0;
}

void *producer(void *arg)
{
    queue_int.Enqueue((*(reinterpret_cast<int *> (arg))));
    return nullptr;
}

void* consumer(void* arg)
{
    queue_int.Dequeue((*(reinterpret_cast<int *>(arg))));
    return nullptr;
}
