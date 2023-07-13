/********************************* 
 * Author: yisrael fisch            
 * File: quick_pop_ordered_list.hpp 
 * 
 * Discription:
 * this container is a sorted container
 * the container can contain any type of data
 * acording the ELEMENT you pass.
 * the container will be sorted accorsing a_compare func 
 * you will pass to the constructor.
 * when you pop an element you will get the the top priority element
 * in O(1)
 * ******************************/
#pragma once
#include <cstddef>//NULL
#include <mutex>//mutex, unique_lock
#include <condition_variable>// condition_variable 

using namespace std;
namespace myspace
{
// a templatic container that can hold any type of element
template <typename ELEMENT>
class Ordered_List
{
public:
   /*   description: creates new doubly linked list 
        params: typename ELEMENT, suitable compare func 
        return value: ptr to this 
        O(1)*/
    Ordered_List(bool (*compare_func)(const ELEMENT &lhs, const ELEMENT &rhs));
    /*  description: release container resources
        params: a suitable compare func 
        O(n)*/
    ~Ordered_List();
    /*  description: insert a new element to the contianer
        params: new ELEMENT 
        O(n) */
    void Push(const ELEMENT &element);
    /*  description: pops the top priority ELEMENT
        return value: the top priority ELEMENT
        O(1) */
    ELEMENT Pop();
    /*  description: check if the list is empty
        return value: true if empty false if not
        O(1) */
    bool IsEmpty();

private:
    class Node;
    void ClearList();
    void RemoveHead();
    Node *m_head;
    bool (* m_compare_func)(const ELEMENT &lhs, const ELEMENT &rhs);
    mutex m_lock;
    condition_variable cond;
};//Ordered_List


//------------------------------------Ordered_List func impl ------------------------

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
//----------------------------------class node & ctor impl---------------------------------
template<typename ELEMENT>
class Ordered_List<ELEMENT>::Node
{
public:
    Node(ELEMENT element);
    ELEMENT m_element;
    Node *next;


};//class node

template<typename ELEMENT>
inline Ordered_List<ELEMENT>::Node::Node(ELEMENT element):m_element(element), next(NULL)
{}

}