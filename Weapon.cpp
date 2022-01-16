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
    // printf("Drawing weapon...\n");
    // get height and width of sprite bitmap
    int w = al_get_bitmap_width(weaponImg);
    int h = al_get_bitmap_height(weaponImg);
    // printf("Image's data gotten.\n");

    // draw bitmap align grid edge
    double dx = circle->x - w / 2, dy = circle->y - h / 2;
    // printf("Transforming...\n");
    // std::pair<int, int> cam = Transform();
    // printf("cam_x = %d, cam_y = %d\n", cam.first, cam.second);
    al_draw_bitmap(weaponImg, dx, dy, 0);
    // printf("Drawn weapon.\n");
}

void
Weapon::Pick()
{
    fire_counter = 50;
    if (circle != NULL) delete circle;
    circle = NULL;
}

void
Weapon::Drop(int drop_x, int drop_y)
{
    circle = new Circle;
    circle->x = drop_x * grid_width + grid_width/2;
    circle->y = drop_y * grid_height + grid_height/2;
    circle->r = 2 * grid_width;
    dropped = false;
}