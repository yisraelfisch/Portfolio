/*********************************
 * Reviewer: 
 * Author: enymorphs			
 * File: shape.hpp
 * ******************************/
#pragma once

#include "point.hpp"
#include "shape.hpp"

namespace ilrd
{

class Circle : public Shape
{
public:
    explicit Circle(const Point& pos ,double angle , double radius = 0); // Ctor 
    virtual ~Circle(); // Dtor
    virtual void Draw(int color);

private:
    double m_radius;
};// Class circle

} // namespace ilrd