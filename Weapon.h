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
#include "Circle.h"
#include "Object.h"
#include "Weapon.h"
#include "global.h"

enum {PISTOL = 0, SMG, AR};

class Weapon : public Object
{
public:
    Weapon();
    virtual ~Weapon();

    // Draw image per frame
    // override virtual function "Object::Draw"
    void Draw();
    void Pick();
    void Drop(int, int);
    void CoolDown() { if (fire_counter < fire_rate) fire_counter++; };
    void Fire() { fire_counter = 0; };
    bool isReadyToFire() { return fire_counter == fire_rate; };

    // functions that return informations of monster
    double getDamage() { return damage; }
    int getFireRate() { return fire_rate; }
    int getSpeed() { return speed; }
    ALLEGRO_BITMAP* getBulletImg() { return bulletImg; }

protected:
    int damage = 10;
    int fire_rate = 10;
    int fire_counter = 0;
    int speed = 10;
    char class_name[20];
    bool dropped;
    ALLEGRO_BITMAP* weaponImg;
    ALLEGRO_BITMAP* bulletImg;
private:
};


#endif // WEAPON_H_INCLUDED
