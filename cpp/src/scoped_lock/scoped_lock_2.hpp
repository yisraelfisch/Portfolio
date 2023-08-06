/*********************************
 * Reviewer: 
 * Author: Elijaho Hanavi
 * File: ScopedLock.hpp
 * ******************************/
#pragma once

#include <pthread.h>
#include <atomic>


namespace ilrd
{

class pthread
{
    public:
        explicit pthread(pthread_mutex_t& mutex);
        ~pthread();

        bool Lock();
        void Unlock();

    private:
        pthread_mutex_t& m_mutex;
        pthread& operator=(const pthread& other);
        pthread(const pthread& other);
};


class spin_lock
{
    public:
        explicit spin_lock();
        ~spin_lock();

        bool Lock();
        void Unlock();
        operator bool() const;

    private:
        bool m_lock;
        spin_lock& operator=(const spin_lock& other);
        spin_lock(const spin_lock& other);
};


template <typename T>
class ScopedLock
{
    public:
        explicit ScopedLock(T& mutex, bool defer = false);	
        ~ScopedLock();

        void Lock();
        void Unlock();
        operator bool() const;
                                                
    private:
        T& m_mutex;
        bool m_isAquired;
        ScopedLock& operator=(const ScopedLock& other);
        ScopedLock(const ScopedLock& other);
};// class ScopedLock 

/* -------pthread------- */

pthread::pthread(pthread_mutex_t& mutex) : m_mutex(mutex)
{
    if(pthread_mutex_init(&m_mutex, NULL))
    {
        perror("pthread_mutex_init");
    }
}

pthread::~pthread()
{
    if(pthread_mutex_destroy(&m_mutex))
    {
        perror("pthread_mutex_destroy");
    }
}

bool pthread::Lock()
{
    pthread_mutex_lock(&m_mutex);

    return true;
}

void pthread::Unlock()
{
    pthread_mutex_unlock(&m_mutex);
}


/* -------spin_lock------- */


spin_lock::spin_lock() : m_lock(0) {}

spin_lock::~spin_lock()
{
    Unlock();
}

bool spin_lock::Lock()
{
    return __atomic_test_and_set(&m_lock, __ATOMIC_SEQ_CST);
}

void spin_lock::Unlock()
{
    __atomic_clear(&m_lock, __ATOMIC_SEQ_CST);
}

spin_lock::operator bool() const
{
    return m_lock;
}


/* -------ScopedLock------- */

template<typename T> 
ScopedLock<T>::ScopedLock(T &mutex, bool defer) : m_mutex(mutex), m_isAquired(false)
{
    if(!defer)
    {
        ScopedLock::Lock();
    }
}

template<typename T>
ScopedLock<T>::~ScopedLock()
{
    ScopedLock::Unlock();
}

template<typename T> 
void ScopedLock<T>::Lock()
{
    m_isAquired = (0 == m_mutex.Lock());
}

template<typename T> 
void ScopedLock<T>::Unlock()
{
    m_mutex.Unlock();

    m_isAquired = false;
}

template<typename T> 
ScopedLock<T>::operator bool() const
{
    return m_isAquired;
}
}