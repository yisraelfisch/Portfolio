
#include <stdio.h>
#include <iostream>
#include "function.hpp" 

using namespace ilrd;

class Str
{
    public:
		explicit Str(){}
        int Print(std::string str)
        {
            std::cout << str << std::endl;
            return 0;
        };
};

class FOO
{
public:

	explicit FOO(int num=33): m_num(num) {}

	int foo(int a)
	{
		return a + m_num;
	}
private:
	int m_num;
};

float Bar(int a)
{
	return static_cast<float>(a) / 17;
}



int main()
{
	int num = 77;
	FOO foo1(num);

	int a = 3;
	Function<int(void)> f1(&FOO::foo, &foo1, a);

	if (f1() != (num + a))
	{
		std::cout << "MemberFunction failed on line " << __LINE__ << std::endl;
	}

	int b = 7;
	Function<float(void)> f2(Bar, b);

	if (f2() != (static_cast<float>(b) / 17))
	{
		std::cout << "FreeFunction failed on line " << __LINE__ << std::endl;
	}

	Function<int(int)> f3(&FOO::foo, &foo1);

	if (f3(a) != (num + a))
	{
		std::cout << "MemberFunction failed on line " << __LINE__ << std::endl;
	}

	Function<float(int)> f4(Bar);
	if (f4(b) != (static_cast<float>(b) / 17))
	{
		std::cout << "FreeFunction failed on line " << __LINE__ << std::endl;
	}
	Str string;
	Function<int(std::string)> f5(&Str::Print, &string);

	f5("Hello_world");


	return 0;
}
