/*************************************** 
file name: stack.hpp
Author: yisrael fisch
*reviewer: 
******************************************/

#include "stack.hpp"

namespace ilrd
{

void Stack::Create(size_t capacity)
{
    m_buff = new int[capacity];
    m_size = 0;
    m_capacity = capacity;
}

void Stack::Destroy()
{
    delete[] m_buff;
    m_buff = NULL;
    m_size = 0;
    m_capacity = 0;
}

void Stack::Push(int element_to_push)
{
    m_buff[m_size++] = element_to_push;
}

void Stack::Pop()
{
    m_size--;
}

int Stack::Peek()
{
    return m_buff[m_size-1];
}

size_t Stack::Size()
{
    return m_size;
}

}
