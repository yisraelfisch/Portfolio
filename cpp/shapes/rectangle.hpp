/*********************************
 * Reviewer: 
 * Author: enymorphs			
 * File: ractangle.hpp
 * ******************************/
#pragma once

#include "point.hpp"
#include "shape.hpp"

namespace ilrd
{

class Rectangle : public Shape
{
public:
    explicit Rectangle(const Point& pos , double height = 0, double width = 0, int color = COLOR_WHITE, double angle = 0); // Ctor 
    virtual ~Rectangle(); // Dtor
    virtual void DrawImp(const Point & pos);

private:
    double m_height; // height
    double m_width; // width

};// Class ractangle

} // namespace ilrd