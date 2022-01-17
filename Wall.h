#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <vector>
#include "Circle.h"
#include "Object.h"
#include "global.h"

class Wall : public Object
{
public:
    Wall(int, int, int, int);
    virtual ~Wall();
    void Draw() { return; }
    bool overlap(int, int);
    int get_xl() { return xl; }
    int get_xr() { return xr; }
    int get_yl() { return yl; }
    int get_yr() { return yr; }

    // Draw image per frame
    // override virtual function "Object::Draw"

protected:
    int xl, xr, yl, yr;

private:
};


#endif // WALL_H_INCLUDED
