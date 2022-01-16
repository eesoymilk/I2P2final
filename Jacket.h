#ifndef JACKET_H_INCLUDED
#define JACKET_H_INCLUDED

#include "Character.h"

class Jacket : public Character
{
public:
    Jacket(int, int);
    ~Jacket();
    void Move(bool(&hold)[4]);
    void setRadianCCW(int, int);
    void Draw();
private:
    ALLEGRO_FONT *hudFont;
    ALLEGRO_BITMAP *icon = NULL;
};


#endif // JACKET_H_INCLUDED
