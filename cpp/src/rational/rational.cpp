/*********************************
 * Reviewer: 
 * Author: yisrael fisch			
 * File: rational.cpp
 * ******************************/

#include "rational.hpp"

namespace ilrd
{
    static int gcd(int num1, int num2)
    {
        if(num1 == 0 || num2 == 0)
        {
            return 1;
        }

        while(num1 != num2)
        {
            if(num1 > num2)
            {
                num1 -= num2;
            }
            else
            {
                num2 -= num1;
            }
        }
        
        return num1;
    } 

    static int Minimize(int num1, int num2)
    {
        return num1/ilrd::gcd(num1, num2);   
    }

    const Rational operator+(const Rational& lhs, const Rational& rhs)
    {
        Rational res(((lhs.Numerator()*rhs.Denominator())+(rhs.Numerator()*lhs.Denominator())),lhs.Denominator()*rhs.Denominator());
        return res;
    }

    const Rational operator-(const Rational& lhs, const Rational& rhs)
    {
        Rational res(((lhs.Numerator()*rhs.Denominator())-(rhs.Numerator()*lhs.Denominator())),lhs.Denominator()*rhs.Denominator());
        return res;
    }

    const Rational operator*(const Rational& lhs, const Rational& rhs)
    {
        Rational res(lhs.Numerator()*rhs.Numerator(), lhs.Denominator()*rhs.Denominator());
        return res;
    }

    const Rational operator/(const Rational& lhs, const Rational& rhs)
    {
        Rational res(rhs.Denominator(), rhs.Numerator());
        return lhs * res;//(rhs.Denominator(), rhs.Numerator());
    }

    bool operator==(const Rational& lhs, const Rational& rhs)
    {       
        return lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator(); 
    }

    bool operator!=(const Rational& lhs, const Rational& rhs)
    {
        return !(lhs == rhs);
    }



    Rational::Rational(int num, int denum): m_numerator(Minimize(num, denum)), m_denominator(Minimize(denum,num))
    {

    }

       Rational& Rational::operator+=(const Rational& other)
    {
        return (*this = *this + other);
    }

    Rational& Rational::operator-=(const Rational& other)
    {
        return (*this = *this - other);
    }
    Rational& Rational::operator*=(const Rational& other)
    {
        return (*this = *this * other);
    }

    Rational& Rational::operator/=(const Rational& other)
    {
        return (*this = *this / other);
    }
}