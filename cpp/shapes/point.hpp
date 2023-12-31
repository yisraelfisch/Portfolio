/*********************************
 * Reviewer: 
 * Author: enymorphs		
 * File: point.hpp
 * ******************************/

#pragma once


namespace ilrd
{

class Point
{
public:
    explicit Point(double x = 0, double y = 0);           //CTOR
    /* Dtor CCtor and operator= to be generated by the compiler */
    
    const Point operator+(const Point& other) const;
    const Point operator-(const Point& other) const;
    Point& operator+=(const Point& other);
    Point& operator-=(const Point& other); 
    const Point operator-() const;  //unary operator - 
    Point& Revolve(const Point& pivot, double angle);
    inline double X() const;
    inline double Y() const;


private:
    double m_x;
    double m_y;
};// Class point

inline double Point::X() const
{
    return m_x;
}

inline double Point::Y() const
{
    return m_y;
}

} // namespace ilrd


