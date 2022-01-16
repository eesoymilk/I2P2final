#ifndef ASSAULT_RIFLE_H_INCLUDED
#define ASSAULT_RIFLE_H_INCLUDED

#include "Weapon.h"

class AssaultRifle : public Weapon
{
public:
    AssaultRifle() : Weapon()
    {
        char buffer[50];
        type = 3;
        damage = 10;
        fire_rate = 10;
        speed = 10;
        strncpy(class_name, "AR", 20);
        sprintf(buffer, "./Weapon/%s.png", class_name);
        printf("Loading Image...\n");
        weaponImg = al_load_bitmap(buffer);
        bulletImg = al_load_bitmap("./Weapon/BULLET.png");
    }
};
#endif // ASSAULT_RIFLE_H_INCLUDED