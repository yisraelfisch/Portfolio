#include <cstdio>
#include "stack.hpp"

int main ()
{
    ilrd::Stack s;

    s.Create(10);
    for(int i = 0; i < 10; ++i)
    {
        s.Push(i);
    }

    printf("size after push is: %lu\n", s.Size());

    for(int i = 0; i < 10; ++i)
    {
        printf("%d\n", s.Peek());
        s.Pop();
    }

    printf("size after pop is:%lu\n", s.Size());

    s.Destroy();

    return 0;
}