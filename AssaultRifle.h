#ifndef ASSAULT_RIFLE_H_INCLUDED
#define ASSAULT_RIFLE_H_INCLUDED

#include "Weapon.h"

class AssaultRifle : public Weapon
{
public:
    AssaultRifle() : Weapon()
    {
        type = 3;
        damage = 21;
        fire_rate = 10;
        speed = 15;
        in_magzine = magzine_size = 30;
        reserved_bullets = 120;
        reload_time = 80;
        strncpy(class_name, "AR", 20);
        LoadData();
    }
    ~AssaultRifle() { printf("Deleting AR...\n"); }
};
#endif // ASSAULT_RIFLE_H_INCLUDED
