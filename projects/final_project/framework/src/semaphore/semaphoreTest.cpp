/*********************************
 * Reviewer: 
 * Author: yisrael fisch
 * File: semaphoreTest.hpp
 * ******************************/
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include "semaphore.hpp"

using namespace ilrd;

void* Post(void *arg)
{
    Semaphore *sem = reinterpret_cast<Semaphore*>(arg);
    while(1)
    {
        sleep(3);
        (*sem).Post();
    }

}

int main()
{
    pthread_t thread_id;
    Semaphore sem;

    pthread_create(&thread_id, NULL, Post, &sem);

    while(1)
    {
        sem.Wait();
        std::cout<<"Thread post "<< std::endl;
    }
}

