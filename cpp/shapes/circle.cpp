/*********************************
 * Reviewer: 
 * Author: enymorphs			
 * File: shape.hpp
 * ******************************/

#include "glut_utils.h"
#include "circle.hpp"
#include "shape.hpp"

namespace ilrd
{
    Circle::Circle(const Point &pos, double radius, int color): Shape(pos, 0, color), m_radius(radius){}

    Circle::~Circle(){}

    void Circle::DrawImp(const Point &pos)
    {
        DrawCircle(this->GetColor(), pos.X(), pos.Y(), this->m_radius);
    }

}

