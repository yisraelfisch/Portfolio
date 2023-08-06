/*********************************
 * Reviewer: 
 * Author: yisrael.fisch
 * File: scoped_lock.hpp
 * ******************************/
#pragma once

#include <pthread.h>

namespace ilrd
{

class ScopedLock
{

public:
	explicit ScopedLock(pthread_mutex_t& mutex);		
	~ScopedLock();
    										
private:
    pthread_mutex_t *m_lock;
    ScopedLock& operator=(const ScopedLock& m);		
    ScopedLock(const ScopedLock& m);		
};// class ScopedLock 

}