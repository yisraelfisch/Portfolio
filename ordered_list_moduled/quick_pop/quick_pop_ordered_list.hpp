/********************************* 
 * Author: yisrael fisch            
 * File: quick_pop_ordered_list.hpp 
 * 
 * ******************************/
#pragma once
#include <cstddef>
#include <mutex>
#include <condition_variable>

using namespace std;
namespace myspace
{

template <typename ELEMENT>
class Ordered_List
{
public:
    Ordered_List(bool (*compare_func)(const ELEMENT &lhs, const ELEMENT &rhs));
    ~Ordered_List();
    void Push(const ELEMENT &element);
    ELEMENT Pop();
    bool IsEmpty();

private:
    class Node;
    void ClearList();
    void RemoveHead();
    Node *m_head;
    bool (* m_compare_func)(const ELEMENT &lhs, const ELEMENT &rhs);
    mutex m_lock;
    condition_variable cond;
};

template <typename ELEMENT>
inline Ordered_List<ELEMENT>::Ordered_List(bool (*compare_func)(const ELEMENT &lhs, const ELEMENT &rhs)): m_compare_func(compare_func), m_head(NULL)
{}

template <typename ELEMENT>
inline Ordered_List<ELEMENT>::~Ordered_List()
{
    if(m_head)
    {
        ClearList();
    }
}

template <typename ELEMENT>
inline void Ordered_List<ELEMENT>::Push(const ELEMENT &element)
{
    Node *new_node = NULL;
    new_node = new Node(element);
    unique_lock<mutex> lock(m_lock);
    
    Node *curr = m_head;
    Node *next = m_head;
    
    if(!m_head)
    {
        m_head = new_node;
        return;
    }

    while(next)
    {
        if(0 == m_compare_func(new_node->m_element, next->m_element))
        {
            curr = next;
            next = next->next;
        }
        else
        {
            break;
        }
    }

    if(next && curr == next)
    {
        new_node->next = m_head;
        m_head = new_node;
    }
    else
    {
        new_node->next = curr->next;
        curr->next = new_node;
    }
    lock.unlock();
    cond.notify_one();

}

template <typename ELEMENT>
inline ELEMENT Ordered_List<ELEMENT>::Pop()
{
    unique_lock<mutex> lock(m_lock);
    while(IsEmpty())
    {
      cond.wait(lock);
    }
    ELEMENT element = m_head->m_element;
   
    RemoveHead();
    lock.unlock();
    
   
    return element;
}

template <typename ELEMENT>
inline bool Ordered_List<ELEMENT>::IsEmpty()
{
   return !m_head ? true:false ;
}

template <typename ELEMENT>
inline void Ordered_List<ELEMENT>::ClearList()
{
    while(m_head)
    {
        RemoveHead();
    }
}

template <typename ELEMENT>
inline void Ordered_List<ELEMENT>::RemoveHead()
{
    Node *temp = m_head;
    m_head = m_head->next;
    delete temp;
}
//----------------------------------class node---------------------------------
template<typename ELEMENT>
class Ordered_List<ELEMENT>::Node
{
public:
    Node(ELEMENT element);
    ELEMENT m_element;
    Node *next;


};

template<typename ELEMENT>
inline Ordered_List<ELEMENT>::Node::Node(ELEMENT element):m_element(element), next(NULL)
{}

}