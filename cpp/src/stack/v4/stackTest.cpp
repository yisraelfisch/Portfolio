#include <iostream>
#include <cstdio>
#include "stack.hpp" 

size_t GetSize(ilrd::Stack stack)
{
    return stack.Size();
}

int main()
{   
    int i = 0;
    int j = 0; 
    ilrd::Stack stack(10);
    
    stack << 0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9;

    if(stack.Size() != 10)
    {
        std::cerr << "Error 1" << std::endl;
    }

    for(i = 9; i >= 0; --i)
    {
        stack >> j;
        if(j != i)
        {
            std::cout << j;
            std::cerr << "Error 2" << std::endl;
        }

        if(stack.Size() != static_cast<size_t>(i + 1))
        {
            std::cerr << "Error 3" << std::endl;
        }
        
        --stack;

        if(stack.Size() != static_cast<size_t>(i))
        {
            std::cerr << "Error 3" << std::endl;
        }
    }

    printf("%ld\n", GetSize(stack));

    return 0;
}