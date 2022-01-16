#ifndef PISTOL_H_INCLUDED
#define PISTOL_H_INCLUDED

#include "Weapon.h"

class Pistol : public Weapon
{
public:
    Pistol() : Weapon()
    {
        char buffer[50];
        
        damage = 10;
        fire_rate = 30;
        speed = 10;
        strncpy(class_name, "PISTOL", 20);
        sprintf(buffer, "./Weapon/%s.png", class_name);
        printf("Loading Image...\n");
        weaponImg = al_load_bitmap(buffer);
        bulletImg = al_load_bitmap("./Weapon/BULLET.png");
    }
};
#endif // PISTOL_H_INCLUDED