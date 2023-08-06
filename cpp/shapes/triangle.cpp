/*********************************
 * Reviewer: 
 * Author: enymorphs			
 * File: triangle.cpp
 * ******************************/

#include "glut_utils.h"
#include "triangle.hpp"
#include "shape.hpp"

namespace ilrd
{
    Triangle ::Triangle (const Point &pos, double height, double width , int color, double angle):
    Shape(pos, angle, color), m_height(height), m_width(width){}

    Triangle ::~Triangle (){}

    void Triangle ::DrawImp(const Point &pos)
    {
        Point p1(pos.X(),(pos.Y()- m_height/2));
        Point p2((pos.X() - m_width/2),(pos.Y()+ m_height/2));
        Point p3((pos.X()+ m_width/2),(pos.Y() + m_height/2));
        

        p1.Revolve(GetPosition(),GetAngle());
        p2.Revolve(GetPosition(),GetAngle());
        p3.Revolve(GetPosition(),GetAngle());
        

        DrawPolygon(this->GetColor(), 3,
        static_cast<int>(p1.X()) , static_cast<int>(p1.Y()),
        static_cast<int>(p2.X()), static_cast<int>(p2.Y() ),
        static_cast<int>(p3.X()), static_cast<int>(p3.Y() ));
        
        
    }

}