#ifndef JACKET_H_INCLUDED
#define JACKET_H_INCLUDED

#include "Character.h"

class Jacket : public Character
{
public:
    Jacket(int spwan_x, int spwan_y) : Character(spwan_x, spwan_y)
    {
        HealthPoint = 20;
        sprites[UNARMED] = 7;
        sprites[PISTOL] = 5;
        sprites[SMG] = 7;
        sprites[AR] = 7;

        strncpy(class_name, "Jacket", 20);
        Load_Img();
    }
    void PickUpWeapon();
};


#endif // JACKET_H_INCLUDED
