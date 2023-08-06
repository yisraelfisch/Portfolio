#pragma once

#include <cstdlib>
#include <atomic>
#include <iostream>

namespace ilrd
{
template<typename T>
class Singleton
{
public:
    explicit Singleton();
    T* operator->();
    ~Singleton() = default; 

    Singleton(Singleton &other) = delete;        //prevent copy
    void operator=(const Singleton &) = delete;    //prevent assignment
private:
    static void CleanUp();
    static T *m_instance;
};// class Singleton

template<typename T>
T* Singleton<T>::m_instance = NULL;//first initialization


template <typename T>
inline Singleton<T>::Singleton()
{
    
    if(NULL == m_instance)
    {
        static bool ctor_started = 0;
        if(! __atomic_test_and_set (&ctor_started, __ATOMIC_SEQ_CST))
        {
            __atomic_store_n (&m_instance, new T(), __ATOMIC_SEQ_CST);
            atexit(CleanUp);
        }
        else
        {
           while(NULL == __atomic_load_n(&m_instance, __ATOMIC_SEQ_CST));
        }
        /* while(!(m_lock.compare_exchange_strong(compare, true,  std::memory_order_seq_cst)));

        if(NULL == __atomic_load_n(&m_instance, __ATOMIC_SEQ_CST))
        {
            __atomic_store_n (&m_instance, new T(), __ATOMIC_SEQ_CST);
            atexit(CleanUp);
        }
        m_lock.store(false); */
    }
}


template <typename T>
inline T *Singleton<T>::operator->()
{
    return m_instance;
}

template <typename T>
inline void Singleton<T>::CleanUp()
{
    std::cout<<"Cleanup\n";
    delete m_instance;
    m_instance = reinterpret_cast<T*>(0xDEADBEEF);// make sure we don't built the object again
    
}

} // namespace ilrd