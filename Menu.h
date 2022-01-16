#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include "Object.h"
#include "Circle.h"
#include "global.h"

class Menu : public Object
{
public:
    Menu();
    virtual ~Menu();

    void Reset();
    void Update(int, int, int, int, int);
    void Draw();

    // Detect if cursor hovers over any of tower on menu
    // If so, return its type
    // Otherwise, return -1
    int MouseIn(int, int);

    // static function that detect if one point is on a line
    // This function is just used to simplify "MouseIn"
    static bool isInRange(int, int, int);

    // Check if current coin is not less than needed coin


private:
    ALLEGRO_FONT *menuFont;
    ALLEGRO_BITMAP *icon = NULL;
    int HealthPoint = 0;
    int Ammo = 0;
    int Magzine_size = 0;
    int reserved_Ammo = 0;
};

#endif // MENU_H_INCLUDED
