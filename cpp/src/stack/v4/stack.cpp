/*************************************** 
file name: stack.cpp
Author: yisrael fisch
*reviewer: 
******************************************/
#include <cstring>
#include "stack.hpp"

namespace ilrd
{
    Stack::Stack(size_t capacity)
    {
        this->m_stack = new int[capacity];
        this->m_capacity = capacity;
        this->m_size = 0;
    }

    Stack::~Stack()
    {
        delete[] m_stack;

        this->m_stack = NULL;
        this->m_capacity = 0;
        this->m_size = 0;
    }

    Stack::Stack(const Stack& other)
    {
        this->m_stack = new int[other.m_capacity];
        this->m_capacity = other.m_capacity;
        this->m_size = other.m_size;
        memcpy(this->m_stack, other.m_stack, m_size * sizeof(int)); 
    }

    void Stack::Push(int element_to_push)
    {
        this->m_stack[m_size++] = element_to_push;
    }

    void Stack::Pop()
    {
        --(this->m_size);
    }

    int Stack::Peek()
    {
        return this->m_stack[m_size - 1];
    }

    size_t Stack::Size()
    {
        return this->m_size;
    }

    void Stack::operator--()
    {
        this->Pop();
    }

    Stack& Stack::operator<<(int element_to_push)
    {
        this->m_stack[m_size++] = element_to_push;
        return *this;
    }

    void Stack::operator>>(int& peeked_element)
    {
        peeked_element = this->m_stack[m_size - 1];
    }

} // namespace ilrd
