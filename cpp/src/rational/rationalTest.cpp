/*********************************
 * Reviewer: 
 * Author: yisrael fisch			
 * File: rationalTest.cpp
 * ******************************/

#include <iostream>
#include "rational.hpp"

int main ()
{
    ilrd::Rational r1;
    ilrd::Rational r2(20, 5);
    ilrd::Rational r3(r2);
    ilrd::Rational r4 = r2;
    ilrd::Rational r5(0, 0);
    ilrd::Rational r6(3, 9);

    std::cout << "r1: nom: " << r1.Numerator() << " r1: denom: " << r1.Denominator() << std::endl;
    std::cout << "r2: nom: " << r2.Numerator() << " r2: denom: " << r2.Denominator() << std::endl; 
    std::cout << "r3: nom: " << r3.Numerator() << " r3: denom: " << r3.Denominator() << std::endl;
    std::cout << "r4: nom: " << r4.Numerator() << " r4: denom: " << r4.Denominator() << std::endl;
    std::cout << "r5: nom: " << r5.Numerator() << " r5: denom: " << r5.Denominator() << std::endl;
    std::cout << "r6: nom: " << r6.Numerator() << " r6: denom: " << r6.Denominator() << std::endl;
    
    r2 = r2 + r2;
    r1 = r2 - r6;
    r3 = r2 * r6;
    r4 = r6 / r2;
    bool t1 = r1 == r1;
    bool t2 = r1 == r2;
    bool t3 = r1 != r1;
    bool t4 = r5 != r1;

    std::cout << "r1: nom: " << r1.Numerator() << " r1: denom: " << r1.Denominator() << std::endl;
    std::cout << "r2: nom: " << r2.Numerator() << " r2: denom: " << r2.Denominator() << std::endl; 
    std::cout << "r3: nom: " << r3.Numerator() << " r3: denom: " << r3.Denominator() << std::endl;
    std::cout << "r4: nom: " << r4.Numerator() << " r4: denom: " << r4.Denominator() << std::endl;
    std::cout << "r5: nom: " << r5.Numerator() << " r5: denom: " << r5.Denominator() << std::endl;
    std::cout << "r6: nom: " << r6.Numerator() << " r6: denom: " << r6.Denominator() << std::endl;
    std::cout << t1 << "\n" << t2 << '\n' << t3 << '\n' << t4 << '\n' << std::endl;
    
    r2 += r2;
    std::cout << "16 " << "r2: nom: " << r2.Numerator() << " r2: denom: " << r2.Denominator() << std::endl; 

    r2 -= r6;
    std::cout << "15.67 " << "r2: nom: " << r2.Numerator() << " r2: denom: " << r2.Denominator() << std::endl; 

    r2 *= r6;
    std::cout << "5.22 " << "r2: nom: " << r2.Numerator() << " r2: denom: " << r2.Denominator() << std::endl; 

    r2 /= r6;
    std::cout << "15.67 " << "r2: nom: " << r2.Numerator() << " r2: denom: " << r2.Denominator() << std::endl; 

    return 0;
}