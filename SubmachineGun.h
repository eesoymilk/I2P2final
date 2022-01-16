#ifndef SUBMACHINE_GUN_H_INCLUDED
#define SUBMACHINE_GUN_H_INCLUDED

#include "Weapon.h"

class SubmachineGun : public Weapon
{
public:
    SubmachineGun() : Weapon()
    {
        char buffer[50];
        type = 2;
        damage = 10;
        fire_rate = 8;
        speed = 10;
        strncpy(class_name, "SMG", 20);
        sprintf(buffer, "./Weapon/%s.png", class_name);
        printf("Loading Image...\n");
        weaponImg = al_load_bitmap(buffer);
        bulletImg = al_load_bitmap("./Weapon/BULLET.png");
    }
};
#endif // SUBMACHINE_GUN_H_INCLUDED