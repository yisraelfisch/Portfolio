#pragma once
#include <set>
#include <iterator>
#include <memory>

#include "function.hpp"
namespace ilrd
{
template<typename EVENT>
class Callback;

//---------------------------foundation classes for observer --------------------//
template<typename EVENT>
class Dispatcher
{
public:
    ~Dispatcher();
    void Add(const Callback<EVENT>& callback);
    void Remove(const Callback<EVENT>& callback);
    void Notify(EVENT event); 
    
private:
    std::set<const Callback <EVENT>*> m_callbacks;//mutable ptr because the ptr is for the dispatcher
};//template<typename EVENT> class Dispatcher


template<typename EVENT>
class Callback
{
public:

    Callback(const Function<void(EVENT)>& function);
    ~Callback();
    void BindDispatcher(const Dispatcher<EVENT>& dispatcher) const;//assgin pointer to the the dispatcher
    void UnBindDispatcher() const;
    void Run(EVENT event) const;
private:
    Function<void(EVENT)> m_function;
    mutable Dispatcher<EVENT> * m_dispatcher;
};//template<typename EVENT> class Callback

//--------------------------------class Dispatcher impl--------------------------------//
template <typename EVENT>
inline Dispatcher<EVENT>::~Dispatcher()
{
    typename std::set<const Callback <EVENT>*>::const_iterator iter ;//const_iterator
    for(iter = m_callbacks.begin(); iter != m_callbacks.end(); ++iter)
    {
        (*iter)->UnBindDispatcher();
        
    }
    m_callbacks.clear();
}

template <typename EVENT>
inline void Dispatcher<EVENT>::Add(const Callback<EVENT> &callback)
{
    m_callbacks.insert(&callback);
    callback.BindDispatcher(*this);
}

template <typename EVENT>
inline void Dispatcher<EVENT>::Remove(const Callback<EVENT> &callback)
{
    m_callbacks.erase(&callback);
}

template <typename EVENT>
inline void Dispatcher<EVENT>::Notify(EVENT event)
{
    
    typename std::set<const Callback <EVENT>*>::const_iterator iter;//const_iterator
    std::cout << "before notify" << std::endl;
    if(false == m_callbacks.empty())
    {
        std::cout << "inside loop" << std::endl;
        for(iter = m_callbacks.begin(); iter != m_callbacks.end(); ++iter)
        {
            (*iter)->Run(event);
        }
    }
}

//--------------------------------class Callback Impl--------------------------------//

template <typename EVENT>
inline Callback<EVENT>::Callback(const Function<void(EVENT)> &function):m_function(function), m_dispatcher(NULL)
{}

template <typename EVENT>
inline Callback<EVENT>::~Callback()
{
    if(m_dispatcher)
    {
        m_dispatcher->Remove(*this);
    }
}

template <typename EVENT>
inline void Callback<EVENT>::BindDispatcher(const Dispatcher<EVENT> &dispatcher) const
{
    m_dispatcher = const_cast<Dispatcher<EVENT>*>(&dispatcher);
}
template <typename EVENT>
inline void Callback<EVENT>::UnBindDispatcher() const
{
    m_dispatcher = NULL;
}
template <typename EVENT>
inline void Callback<EVENT>::Run(EVENT event) const
{
    m_function(event);
}

}
