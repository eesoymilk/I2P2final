#ifndef JACKET_H_INCLUDED
#define JACKET_H_INCLUDED

#include "Character.h"

class Jacket : public Character
{
public:
    Jacket() : Character()
    {
        state_count = 3;
        direction_count[LEFT] = 1;
        direction_count[RIGHT] = 6;
        direction_count[UP] = 1;
        direction_count[DOWN] = 1;

        HealthPoint = 20;
        speed = 1;
        worth = 5;
        score = 50;

        strncpy(class_name, "Jacket", 20);

        Load_Move();
    }
};


#endif // JACKET_H_INCLUDED
