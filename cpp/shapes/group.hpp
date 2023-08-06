/*********************************
 * Reviewer: 
 * Author: enymorphs			
 * File: group.hpp
 * ******************************/
#pragma once

#include <cstddef>
#include "point.hpp"
#include "shape.hpp"

namespace ilrd
{

class Group : public Shape
{
public:
    explicit Group(const Point& pos ,int color = COLOR_BLACK, double angle = 0); // Ctor 
    virtual ~Group(){}; // Dtor
    virtual void DrawImp(const Point & pos);
    const Group& Add(Shape* shape);

private:
    size_t m_members; // height
    Shape* shapes[30]; // width

};// Class ractangle

} // namespace ilrd