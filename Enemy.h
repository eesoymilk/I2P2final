#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "Character.h"

class Enemy : public Character
{
public:
    Enemy(int, int);
    ~Enemy();
    void Move();
    void setRadianCCW(int, int);
    void Draw();
};

#endif // ENEMY_H_INCLUDED
