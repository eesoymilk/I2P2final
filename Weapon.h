#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Circle.h"
#include "Object.h"
#include "Weapon.h"
#include "global.h"

class Weapon : public Object
{
public:
    Weapon();
    ~Weapon();

    // Draw image per frame
    // override virtual function "Object::Draw"
    void Draw();
    void Pick();
    void Drop(int, int);
    void CoolDown() { if (fire_counter < fire_rate) fire_counter++; };
    bool Fire();
    void StartReload();
    void Reload();
    bool isReloading() { return reloading; };
    bool isDropped() { return dropped; };

    // functions that return informations of monster
    int getType() { return type; }
    double getDamage() { return damage; }
    int getFireRate() { return fire_rate; }
    int getSpeed() { return speed; }
    int getIn() { return in_magzine; }
    int getSize() { return magzine_size; }
    int getAmmo() { return in_magzine; }
    int getMagSize() { return magzine_size; }
    int getReserved() { return reserved_bullets; }
    ALLEGRO_BITMAP* getBulletImg() { return bulletImg; }

protected:
    int type, damage, fire_rate;
    int fire_counter = 0, reload_counter = 0;
    int speed;
    char class_name[20];
    int in_magzine, magzine_size, reserved_bullets, reload_time;
    bool dropped, reloading;
    ALLEGRO_BITMAP* weaponImg;
    ALLEGRO_BITMAP* bulletImg;
    ALLEGRO_SAMPLE* sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE* Sound = NULL;
    ALLEGRO_SAMPLE_INSTANCE* ReloadSound = NULL;

private:
};


#endif // WEAPON_H_INCLUDED
