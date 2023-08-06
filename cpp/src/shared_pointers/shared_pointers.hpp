/*********************************
 * Reviewer: 
 * Author: Scott Meyers
 * File Name: SharedPointer.hpp
 * ******************************/

#pragma once

#include <cstddef>

namespace ilrd
{

template<typename T>
class SharedPointer
{
public:
	/*non-explicit*/SharedPointer(T* ptr = NULL);
    template<typename O>
    /*non-explicit*/SharedPointer(const SharedPointer<O>& derived);
	~SharedPointer();
    SharedPointer(const SharedPointer& other); 
	SharedPointer& operator=(const SharedPointer& other);
    T& operator *() const;
	T* operator->() const;

private:
    

	T* m_ptr;
	size_t* m_counter;
    void Attach();
    size_t Detach();
    void CleanUp();
    void Assign(const SharedPointer& other);

}; // class SharedPointer


template<typename T>
SharedPointer<T>::SharedPointer(T *ptr): m_ptr(ptr), m_counter(new size_t (1))
{}

template<typename T>
SharedPointer<T>::~SharedPointer()
{
        CleanUp();    
}

template<class T>
void SharedPointer<T>::CleanUp()
{
    if(!Detach())
    {
        delete m_ptr;
        delete m_counter;
    }
}

template<typename T>
void SharedPointer<T>::Attach()
{
    ++(*m_counter);
}

template<typename T>
size_t SharedPointer<T>::Detach()
{
    return (--(*m_counter));
}

template<typename T>
SharedPointer<T>::SharedPointer(const SharedPointer<T> &other)
{
    Assign(other);
}

template<class T>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<T> &other)
{
    if(this != &other)
    {
        CleanUp();
        Assign(other);
        return *this;
    }
}

template<class T>
void SharedPointer<T>::Assign(const SharedPointer<T> &other)
{
    this->m_ptr = other.m_ptr;
    this->m_conter = other.m_counter;
    Attach();
}

template<class T>
T& SharedPointer<T>::operator*() const
{
    return *m_ptr;
}

template<class T>
T* SharedPointer<T>::operator->() const
{
    return m_ptr;
}

template<class T>
template<class O>
SharedPointer<T>::SharedPointer(const SharedPointer<O> &derived)
{
    this->m_ptr = derived.m_ptr;
    this->m_counter = derived.m_counter;
}


} // namespace ilrd


