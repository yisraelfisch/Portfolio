/*********************************
 * Reviewer: 
 * Author: enymorphs			
 * File: triangle.cpp
 * ******************************/

#include "glut_utils.h"
#include "shape.hpp"
#include "group.hpp"

namespace ilrd
{
    Group ::Group (const Point &pos,int color, double angle):
    Shape(pos, angle, color), m_members(0){}


    void Group ::DrawImp(const Point &pos)
    {
        for(size_t i = 0; i < m_members; i++)
        {
            shapes[i]->Draw(pos);
        }
         
    }

    const Group &Group::Add(Shape *shape)
    {
        shapes[m_members++] = shape;
        return *this;
    }
}