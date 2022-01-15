#ifndef PISTOL_H_INCLUDED
#define PISTOL_H_INCLUDED

#include "Weapon.h"

class Pistol : public Weapon
{
public:
    Pistol() : Weapon()
    {
        char* buffer;
        
        damage = 10;
        fire_rate = 1;
        speed = 10;
        strncpy(class_name, "Pistol", 20);
        sprintf(buffer, "./weapon/%s.png", class_name);
        weaponImg = al_load_bitmap(buffer);
    }
};
#endif // PISTOL_H_INCLUDED