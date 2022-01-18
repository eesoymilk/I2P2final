#ifndef PISTOL_H_INCLUDED
#define PISTOL_H_INCLUDED

#include "Weapon.h"

class Pistol : public Weapon
{
public:
    Pistol() : Weapon()
    {
        type = 1;
        damage = 19;
        fire_rate = 25;
        speed = 12;
        in_magzine = magzine_size = 10;
        reserved_bullets = 60;
        reload_time = 80;
        strncpy(class_name, "PISTOL", 20);
        LoadData();
    }
};
#endif // PISTOL_H_INCLUDED
