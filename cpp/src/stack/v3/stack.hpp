/*************************************** 
file name: stack.hpp
Author: yisrael fisch
*reviewer: 
******************************************/

#ifndef __STACK_HPP__
#define __STACK_HPP__

#include <cstddef> //size_t

namespace ilrd
{

class Stack
{
public:
    /*Stack();*/
    explicit Stack(size_t capacity = 1000);
    ~Stack();
    Stack(const Stack& other_);
    void Push(int);
    void Pop();
    int Peek();
    size_t Size();
private:
    int *m_buff;
    size_t m_size;
    size_t m_capacity;
};
size_t GetSize(Stack stack);
//size_t Size(Stack stack);)
}

#endif /* __STACK_HPP__ */