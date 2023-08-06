/*********************************
 * Reviewer: 
 * Author: yisrael fisch			
 * File: rational.hpp
 * ******************************/

#pragma once

#include <cstddef> /* size_t */
#include <ostream> 


namespace ilrd
{

class Rational;

const Rational operator+(const Rational& lhs, const Rational& rhs);
const Rational operator-(const Rational& lhs, const Rational& rhs);
const Rational operator*(const Rational& lhs, const Rational& rhs);
const Rational operator/(const Rational& lhs, const Rational& rhs);
bool operator==(const Rational& lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);

class Rational
{
public:
    /* non-explicit */ Rational(int num = 0, int denum = 1);           //CTOR
    /* Dtor CCtor and operator= to be generated by the compiler */

    inline int Numerator() const
    {
        return this->m_numerator;
    }
    
    inline int Denominator() const
    {
        return this->m_denominator;
    }

    Rational& operator+=(const Rational& other);
    Rational& operator-=(const Rational& other);
    Rational& operator*=(const Rational& other);
    Rational& operator/=(const Rational& other);


private:
    int m_numerator;
    int m_denominator;
};// Class : Rational

} // namespace ilrd
