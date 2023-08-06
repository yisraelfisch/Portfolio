#include "imonitor.hpp"
#include "select.hpp"
#include "reactor.hpp"
#include <unistd.h>

using namespace ilrd;

int PrtInput(int fd)
{   
    char buff[10] = {0};
    if(read(fd, buff, 10) == -1)
    {
        perror ("read");
    }

    std::cout << buff << std::endl;

    return 0;
}

int main()
{
    Function<int(void)> f1(&PrtInput, 0);
    Reactor<Select> r1;

    r1.RegisterReadHandler(0, f1);
    r1.Run();

    return 0;
}