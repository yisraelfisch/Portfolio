#include "glut_utils.h"
#include "point.hpp"
#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "group.hpp"

namespace ilrd
{
    
Group *newGroup = new Group(Point(0,0));
Shape *ptr1 = new Circle(Point(200,200), 60,COLOR_RED|COLOR_FILL);
Shape *ptr2 = new Circle(Point(800,200), 60, COLOR_GREEN|COLOR_FILL);
Shape *ptr3 = new Circle(Point(500,900), 60, COLOR_YELLOW|COLOR_FILL);
Shape *ptr4 = new Rectangle(Point(499,499),200,200, COLOR_BLUE);
Shape *ptr5 = new Triangle(Point(499,490),100,100, COLOR_BLUE);
Shape *ptr6 = new Triangle(Point(499,510),100,100, COLOR_BLUE, 3.14);
Shape *ptr7 = new Triangle(Point(499,510),100,100, COLOR_BLUE, 3.14/2);
Shape *ptr8 = new Triangle(Point(499,490),100,100, COLOR_BLUE, 3.14);

static void DrawFunction();
static int TimerFunction();

} // namespace ilrd

int main(int argc,char **argv)
{
    ilrd::newGroup->Add(ilrd::ptr5);
    ilrd::newGroup->Add(ilrd::ptr6);
    ilrd::newGroup->Add(ilrd::ptr7);
    ilrd::newGroup->Add(ilrd::ptr8);
    DrawInit(argc, argv, 1000, 1000, ilrd::DrawFunction);
    DrawSetTimerFunc(ilrd::TimerFunction, 50);

    DrawMainLoop();

    return 0;
}

static void ilrd::DrawFunction()
{
    ptr1->Draw(Point(0,0));
    ptr2->Draw(Point(0,0));
    ptr3->Draw(Point(0,0));
    ptr4->Draw(Point(0,0));
    //ptr5->Draw(Point(0,0));
    //ptr6->Draw(Point(0,0));
    newGroup->Draw(Point(0,0));
}

static int ilrd::TimerFunction()
{
    ptr1->Revolve(Point(499,499), 3.14/100);
    ptr2->Revolve(Point(499,499), 3.14/100);
    ptr3->Revolve(Point(499,499), 3.14/100);
    ptr4->Rotate(-3.14/100);
    //ptr5->Rotate(3.14/100);
    //ptr6->Rotate(3.14/100);
    newGroup->Revolve(Point(499,499), 3.14/100);
    return 1;
}