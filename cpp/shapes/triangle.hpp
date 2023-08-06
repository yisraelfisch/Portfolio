/*********************************
 * Reviewer: 
 * Author: enymorphs			
 * File: triangle.hpp
 * ******************************/
#pragma once

#include "point.hpp"
#include "shape.hpp"

namespace ilrd
{

class Triangle : public Shape
{
public:
    explicit Triangle(const Point& pos , double height = 0, double width = 0, int color = COLOR_WHITE, double angle = 0); // Ctor 
    virtual ~Triangle(); // Dtor
    virtual void DrawImp(const Point & pos);

private:
    double m_height; // height
    double m_width; // width

};// Class Triangle

} // namespace ilrd