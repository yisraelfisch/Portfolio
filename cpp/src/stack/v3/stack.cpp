/*************************************** 
file name: stack.hpp
Author: yisrael fisch
*reviewer: 
******************************************/
#include <cstring>//memcpy
#include "stack.hpp"


namespace ilrd
{

/*Stack::Stack()
{
    m_buff = new int[1000];
    m_size = 0;
    m_capacity = 1000;
}*/
Stack::Stack(size_t capacity)
{
    m_buff = new int[capacity];
    m_size = 0;
    m_capacity = capacity;
}

Stack::~Stack()
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

Stack::Stack(const Stack& other_)
{
    m_buff = new int[other_.m_capacity];
    m_size = other_.m_size;
    m_capacity = other_.m_capacity;
    memcpy(m_buff, other_.m_buff, m_size * sizeof(int));
}

size_t GetSize(Stack stack)
{
    return stack.Size();
}
}
