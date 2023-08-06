#include <cstdio>
#include "stack.hpp"

const size_t STACK_SIZE = 10;

int main ()
{
    ilrd::Stack s;

    //s.Create(1000);
    for(int i = 0; i < static_cast<int> (STACK_SIZE); ++i)
    {
        s.Push(i);
    }

    printf("size after push is: %lu\n", s.Size());

    for(int i = 0; i < static_cast<int> (STACK_SIZE); ++i)
    {
        printf("%d\n", s.Peek());
        s.Pop();
    }

    printf("size after pop is:%lu\n", s.Size());

   // s.Destroy();

    return 0;
}