#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "Character.h"

class Enemy : public Character
{
public:
    Enemy(int, int);
    ~Enemy();
    void Move(double, double, std::vector<Wall*>);
    void FireWeapon(double, double);
    void Assault(int, int, std::vector<Wall*>);
    void setRadianCCW(int, int);
    void setSpeed(int);
    void Draw();
protected:
    int speed = 0;
    double pos_x, pos_y;
};

#endif // ENEMY_H_INCLUDED