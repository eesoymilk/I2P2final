#ifndef JACKET_H_INCLUDED
#define JACKET_H_INCLUDED

#include "Character.h"

class Jacket : public Character
{
public:
    Jacket() : Character()
    {
        state = 0;
        HealthPoint = 20;
        speed = 1;
        worth = 5;
        score = 50;

        strncpy(class_name, "Jacket", 20);

        Load_Move();
    }
};


#endif // JACKET_H_INCLUDED
