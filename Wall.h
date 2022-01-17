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
    void Draw() {
        std::pair<int, int> cam = Transform();
        al_draw_bitmap(tmp, cam.first, cam.second, 0);
    }
    bool overlap(int, int);
    int get_xl() { return xl; }
    int get_xr() { return xr; }
    int get_yl() { return yl; }
    int get_yr() { return yr; }
    int get_type() { return type; }

    // Draw image per frame
    // override virtual function "Object::Draw"

protected:
    ALLEGRO_BITMAP *tmp = NULL;
    int xl, xr, yl, yr;
    int type;

private:
};


#endif // WALL_H_INCLUDED
