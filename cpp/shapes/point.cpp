#include <math.h>
#include "point.hpp"

namespace ilrd
{
Point::Point(double x, double y): m_x(x), m_y(y){}

const Point Point::operator+(const Point &other) const
{
    return Point(*this) += other;
}

const Point Point::operator-(const Point &other) const
{
    return Point(*this) += other;
}

Point& Point::operator+=(const Point &other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    return *this;
}

Point& Point::operator-=(const Point &other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    return *this;
}

const Point Point::operator-() const
{
    return Point(-m_x, -m_y);
}

Point &Point::Revolve(const Point &pivot, double angle)
{
    double sinVal = sin(angle);
    double cosVal = cos(angle);

    /* translate point back to origin: */
    double xOffset = this->m_x - pivot.m_x;
    double yOffset = this->m_y - pivot.m_y;

    /* rotate point & translate point back: */
    this->m_x = pivot.m_x + xOffset * cosVal - yOffset * sinVal;
    this->m_y = pivot.m_y + xOffset * sinVal + yOffset * cosVal;

    return *this;
}



}
