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
    explicit Circle(const Point& pos , double radius = 0, int color = COLOR_WHITE); // Ctor 
    virtual ~Circle(); // Dtor
    virtual void DrawImp(const Point & pos);

private:
    double m_radius;
};// Class circle

} // namespace ilrd

