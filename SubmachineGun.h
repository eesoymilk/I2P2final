#ifndef SUBMACHINE_GUN_H_INCLUDED
#define SUBMACHINE_GUN_H_INCLUDED

#include "Weapon.h"

class SubmachineGun : public Weapon
{
public:
    SubmachineGun() : Weapon()
    {
        type = 2;
        damage = 9;
        fire_rate = 8;
        speed = 12;
        in_magzine = magzine_size = 30;
        reserved_bullets = 150;
        reload_time = 80;
        strncpy(class_name, "SMG", 20);
        LoadData();
    }
};
#endif // SUBMACHINE_GUN_H_INCLUDED
