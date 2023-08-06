#include <iostream>//cout
#include "string.hpp"
    
using namespace ilrd;

int main()
{
    RcString s1; // default ctor
    RcString s2("Guns N Roses"); // ctor + str as argument
    RcString s3(s2); // ctor + str as argument
    RcString s4("November Rain"); // ctor + str as argument

    if(s3 != "Guns N Roses")
    {
        std::cout << "Error- != operator line: %d" <<__LINE__<< std::endl;
    }

    s1 = s3;

    if(s3 != s1)
    {
        std::cout << "Error- != operator line: %d" <<__LINE__<< std::endl;

    }

    if(s4 == s1)
    {
        std::cout << "Error- != operator line:" <<__LINE__<< std::endl;
    }

    s4 = s1;

    if("November Rain" == s4)
    {
        std::cout << "Error- != operator line:" <<__LINE__<< std::endl;
    }

    if("Guns N Roses" != s4)
    {
        std::cout << "Error- != operator line: " <<__LINE__<< std::endl;
    }

    if(!(s4 == s1))
    {
        std::cout << "Error- != operator line:" <<__LINE__<< std::endl;
    }
    
    s2[0] = 'R';
    s2[1] = 'o';

    std::cout << s4 << std::endl;
    std::cout << s2 << std::endl;

    char c = s2[0];

    std::cout << c << std::endl;
    
    RcString s5("Hello");
    RcString s6 = s5;
    RcString s7("World");
    RcString s8(s7);
    
    s6[0] = 'J';
    s7[0] = 'Z';

    if(!(s5 < s6))
    {
        std::cout << "Error- < operator line: " <<__LINE__<< std::endl;

    }

    if(s6 > s7)
    {
        std::cout << "Error- > operator line: " <<__LINE__<< std::endl;
    }

    if(!(s7 > s8))
    {
        std::cout << "s4 is bigger then s3" << std::endl;
    }

    std::cout << "s7: " << s7 << " " << "s8: " << s8 << std::endl;
    std::cout << "s5: " << s5 << " " << "s6: " << s6 << std::endl;

    s7[0] = s6[0] = 'y';

    std::cout << "s7: " << s7 << " " << "s6: " << s6 << std::endl;


    return 0;
}