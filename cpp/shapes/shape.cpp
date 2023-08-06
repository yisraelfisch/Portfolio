/*********************************
 * Reviewer: 
 * Author: enymorphs			
 * File: shape.hpp
 * ******************************/

#include "shape.hpp"

namespace ilrd
{
    Shape::Shape(const Point &pos, double angle, int color): m_pos(pos),m_angle(angle), m_color(color){}

    void Shape::Move(const Point &pos)
    {
        this->m_pos = pos;
    }

    void Shape::Step(const Point &pos)
    {
        this->m_pos += pos;
    }

    void Shape::Rotate(double angle)
    {
        this->m_angle += angle;
    }

    void Shape::Revolve(const Point &pivot, double angle)
    {
        this->m_pos = this->m_pos.Revolve(pivot, angle);
    }

    void Shape::Draw(const Point& origin)
    {
        DrawImp(origin + this->m_pos);
    }




}