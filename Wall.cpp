#include "Wall.h"
#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))
#define thick 30

Wall::Wall(int x1, int y1, int x2, int y2) : Object()
{
    circle = new Circle;
    circle->x = (x1 + x2) / 2;
    circle->y = (y1 + y2) / 2;
    circle->r = thick;
    if(x1 == x2){
        xl = x1 - thick;
        xr = x1 + thick;
        yl = min(y1, y2);
        yr = max(y1, y2);
        type = 0;
    }
    else{
        yl = y1 - thick;
        yr = y1 + thick;
        xl = min(x1, x2);
        xr = max(x1, x2);
        type = 1;
    }
    tmp = al_load_bitmap("./SMG_icon.png");
}

Wall::~Wall()
{
    if (circle != NULL) delete circle;
    al_destroy_bitmap(tmp);
}

bool
Wall::overlap(int x, int y){
    if((x >= xl && x <= xr) && (y >= yl && y <= yr)) return true;
    else return false;
}

