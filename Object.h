#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <utility>
#include <cmath>
#include "Circle.h"
#include "global.h"
#define PI 3.1415926

class Object {
public:
    Object() {}
    ~Object() {};

    // pure function for drawing object
    virtual void Draw() = 0;
    double Distance(int, int);

    int getX() { return circle->x; }
    int getY() { return circle->y; }
    int getRadius() { return circle->r; }
    std::pair<double, double> UnitVector(double X, double Y);

    Circle* getCircle() const { return circle; }

    std::pair<int, int> Transform();

protected:
    Circle *circle;

};
#endif // OBJECT_H_INCLUDED
