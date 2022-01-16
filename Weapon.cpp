#include "Weapon.h"

#define InitX 0
#define InitY 0
#define MaxSpeed 3
#define Acceleration 1
#define PI 3.1415926
#define SCALE 2

// set counter frequency of drawing moving animation
const int draw_frequency = 10;

Weapon::Weapon()
{
    circle = new Circle;
    circle->r = 2 * grid_width;
    dropped = false;
    strncpy(class_name, "Weapon", 20);
}


Weapon::~Weapon()
{
    al_destroy_bitmap(weaponImg);
    al_destroy_bitmap(bulletImg);
    al_destroy_bitmap(icon);
    if (circle != NULL) delete circle;
    al_destroy_sample(sample);
    al_destroy_sample_instance(Sound);
    al_destroy_sample_instance(ReloadSound);
}

void
Weapon::Draw()
{
    if (dropped) {
        // printf("Drawing weapon...\n");
        // get height and width of sprite bitmap
        int w = al_get_bitmap_width(weaponImg);
        int h = al_get_bitmap_height(weaponImg);
        // printf("Image's data gotten.\n");

        // draw bitmap align grid edge
        // double dx = circle->x - w / 2, dy = circle->y - h / 2;
        // printf("Transforming...\n");
        auto [dx, dy] = Transform();
        // printf("cam_x = %d, cam_y = %d\n", cam.first, cam.second);
        al_draw_bitmap(weaponImg, dx, dy, 0);
        // printf("Drawn weapon.\n");
    }
}

void
Weapon::Pick()
{
    // PICKING UP WEAPON SOUND EFFECT
    fire_counter = 0;
    dropped = false;
}

void
Weapon::Drop(int drop_x, int drop_y)
{
    // DROPPING WEAPON SOUND EFFECT
    circle->x = drop_x;
    circle->y = drop_y;
    dropped = true;
    printf("Dropped\n");
}

bool
Weapon::Fire()
{
    if (fire_counter < fire_rate)   return false;
    if (in_magzine == 0) {
        // DRY MAG SOUND EFFECT
        return false;
    }
    in_magzine--;
    fire_counter = 0;
    al_play_sample_instance(Sound);// FIRING SOUND EFFECT
    return true;
}

void
Weapon::StartReload()
{
    if (reserved_bullets == 0) {
        // RELOAD BUT NO AMMO SOUND EFFECT
        return;
    }
    if (in_magzine == magzine_size) {
        // RELOAD BUT FULL MAG EFFECT
        return;
    }
    reloading = true;
    reload_counter = 0;
    return;
}

void
Weapon::Reload()
{
    if (reload_counter < reload_time) {
        reload_counter++;
        return;
    }
    al_play_sample_instance(Sound);// RELOAD SOUND EFFECT
    int to_reload = magzine_size - in_magzine;
    if (reserved_bullets >= to_reload) {
        reserved_bullets -= to_reload;
        in_magzine = magzine_size;
    } else {
        in_magzine += reserved_bullets;
        reserved_bullets = 0;
    }
    fire_counter = 0;
    reloading = false;
    return;
}
