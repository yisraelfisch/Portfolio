#include <iostream>
#include <vector>
#include "string.hpp"

int main()
{
    #if 1
    std::vector<ilrd::String> v1(30);
#else
  // your old testing code
    ilrd::String s1; // default ctor
    ilrd::String s2("String-Cpp"); // ctor + str as argument
    ilrd::String s3(s2); // cctor
    ilrd::String s4("second string"); // ctor + str as argument
    const ilrd::String s5("Const String"); // ctor + str as argument
    ilrd::String s6 = "str6";

    s4 = s3; // assinment operator + str as argument + cctor
    
    if(!(s4 == s3)) // == operator
    {
        std::cout << "Error- == operator" << std::endl;
    }

    if(!(s2 == s4)) // == operator
    {
        std::cout << "Error- == operator-other side" << std::endl;
    }

    s4 = "new string";

    if(!(s4 != s2)) // != operator
    {
        std::cout << "Error- != operator" << std::endl;
    }

    s4 = &s5[8]; // const! [] operator

    std::cout << "s4 = " <<s4 <<std::endl; 

    if(!(s4 == "ring"))
    {
        std::cout << "Error-[] operator" << std::endl;
    }

    s6 = "changing the str";

    if(!(s6 == "changing the str"))
    {
        std::cout << "Error-[] operator" << std::endl;
    }

    if(!(s4 > s2))
    {
        std::cout << "Error > operator" << std::endl;
    }

    if(!(s2 < s4))
    {
        std::cout << "Error > operator" << std::endl;
    }

    if(!("S" < "s"))
    {
        std::cout << "Error > operator" << std::endl;
    }
    // std::cout << "s5 = " <<s5 <<std::endl; 

#endif
    return 0;
}