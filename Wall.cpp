#include "Wall.h"
#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))

Wall::Wall(int x1, int y1, int x2, int y2)
{
    circle = new Circle;
    circle->x = (x1 + x2) / 2;
    circle->y = (y1 + y2) / 2;
    circle->r = 5;
    if(x1 == x2){
        xl = x1 - 5;
        xr = x1 + 5;
        yl = min(y1, y2);
        yr = max(y1, y2);
    }
    else{
        yl = y1 - 5;
        yr = y1 + 5;
        xl = min(x1, x2);
        xr = max(x1, x2);
    }
}

Wall::~Wall()
{
    if (circle != NULL) delete circle;
}

bool
Wall::overlap(int x, int y){
    if((x >= xl && x <= xr) && (y >= yl && y <= yr)) return true;
    else return false;
}


