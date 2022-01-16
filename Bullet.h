#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include "Object.h"
#include "Circle.h"

#define abs(x) ((x) > 0? (x) : -(x))

class Bullet : public Object
{
public:
    Bullet(Circle*, double, double, int, int, ALLEGRO_BITMAP*);
    virtual ~Bullet();

    // override virtual function "Object::Draw"
    void Move();
    void Draw();
    int getDamage() { return damage; }
    double getRadianCCW() { return radian_ccw; }

    static double volume;

protected:
    ALLEGRO_BITMAP *bulletImg;
    ALLEGRO_SAMPLE *sample;
    ALLEGRO_SAMPLE_INSTANCE *arrow = NULL;

private:
    int speed = 8;
    int damage = 5;
    double pos_x, pos_y, unit_x, unit_y;
    double radian_ccw;
};

#endif // BULLET_H_INCLUDED
