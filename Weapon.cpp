#include "Weapon.h"

#define InitX 0
#define InitY 0
#define MaxSpeed 3
#define Acceleration 1
#define PI 3.1415926
#define SCALE 2

const char  state_name[][10] = {"UNARMED", "PISTOL", "SMG", "AR"};

// set counter frequency of drawing moving animation
const int draw_frequency = 10;

Weapon::Weapon()
{
    circle = NULL;
    dropped = false;
    strncpy(class_name, "Weapon", 20);
}


Weapon::~Weapon()
{
    al_destroy_bitmap(weaponImg);
    al_destroy_bitmap(bulletImg);
    if (circle != NULL) delete circle;
}

void
Weapon::Draw()
{
    // get height and width of sprite bitmap
    int w = al_get_bitmap_width(weaponImg);
    int h = al_get_bitmap_height(weaponImg);

    // draw bitmap align grid edge
    double dx = circle->x - w / 2, dy = circle->y - h / 2;
    al_draw_bitmap(weaponImg, dx, dy, 0);
}

void
Weapon::Pick()
{
    if (circle != NULL) delete circle;
    circle = NULL;
}

void
Weapon::Drop(int x, int y)
{
    circle = new Circle;
    circle->x = InitX * grid_width + grid_width/2;
    circle->y = InitY * grid_height + grid_height/2;
    circle->r = 2 * grid_width;
    dropped = false;
}