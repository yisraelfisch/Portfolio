/*************************************** 
file name: stack.hpp
Author: yisrael fisch
*reviewer: 
******************************************/

#ifndef __STACK_HPP__
#define __STACK_HPP__

#include <cstddef>

namespace ilrd
{
    class Stack
    {
        public:
            explicit Stack(size_t capacity = 0);
            ~Stack();
            Stack(const Stack& other);
            size_t Size();
            void operator--();
            Stack& operator<<(int element_to_push);
            void operator>>(int& peeked_element);

        private:
            void Push(int element_to_push);
            int Peek();
            void Pop();
            size_t m_size;
            size_t m_capacity;
            int *m_stack;
    };

} // namespace ilrd

#endif // __STACK_HPP__