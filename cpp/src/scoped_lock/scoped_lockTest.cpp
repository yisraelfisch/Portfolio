/*********************************
 * Reviewer: 
 * Author: yisrael.fisch
 * File: scoped_lockTest.cpp
 * ******************************/

#include "scoped_lock.hpp"

#include <pthread.h>
#include <iostream>
#include <unistd.h> /* sleep */
#include "scoped_lock.hpp" 

#define RAII_LOCK //put this line in comment if you want to torn off the lock
#define N 5

using namespace ilrd;
using namespace std;

pthread_mutex_t mutex;
bool g_sits[N] = {0};

void *OrderSits(void *num_of_sits)
{
    for(size_t i = 0; i < *(static_cast<size_t*> (num_of_sits)); i++)
    {
        if(g_sits[i])
        {
            #ifdef RAII_LOCK
            ScopedLock lock(mutex);
            #endif
            cout << "sit " << i << " is allredy taken" << endl;
        }
        else
        {
            #ifdef RAII_LOCK
            ScopedLock lock(mutex);
            #endif
            g_sits[i] = 1;
            cout << "sit " << i << " is your's" << endl;

        }    
    }
        return NULL;
}

void *CancelSits(void *num_of_sits)
{

    for(size_t i = 0; i < *(static_cast<size_t*> (num_of_sits)); i++)
    {
        if(!g_sits[i])
        {
            #ifdef RAII_LOCK
            ScopedLock lock(mutex);
            #endif
            cout << "sit " << i << " is allredy canceled " << endl;
        }
        else
        {
            #ifdef RAII_LOCK
            ScopedLock lock(mutex);
            #endif
            g_sits[i] = 0;
            cout << "sit " << i << " is canceld" << endl;
        }    
    }
    return NULL;
}


int main()
{
    size_t num_of_sits = N;
	pthread_t thread1, thread2;

	pthread_mutex_init(&mutex, NULL);

	pthread_create(&thread1, NULL, OrderSits, &num_of_sits);
	pthread_create(&thread2, NULL, CancelSits, &num_of_sits);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);


	return 0;
}


