#include "imonitor.hpp"
#include "select.hpp"
#include <iostream>
#include <unistd.h>



using namespace ilrd;

int main()
{
    char input[10] = {};

    Select s1;
    
    s1.SetRead(0);
    
    if(s1.WaitForEvent())
    {
        if(!s1.GetNextReadFd())
        {
            read(0, input, 10);
        }
    }

    std::cout << input << std::endl;

    return 0;
}
