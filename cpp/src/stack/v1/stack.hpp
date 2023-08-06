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
    void Create(size_t);
    void Destroy();
    void Push(int);
    void Pop();
    int Peek();
    size_t Size();
private:
    int *m_buff;
    size_t m_size;
    size_t m_capacity;
};
}
#endif /* __STACK_HPP__ */