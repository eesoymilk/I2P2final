#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Circle.h"
#include "Object.h"
#include "Attack.h"
#include "global.h"

enum {UNARMED = 0, PISTOL, SMG, AR};

#ifndef KEYS
#define KEYS
#define KeysUsed 5
enum {W_KEY=0, A_KEY, S_KEY, D_KEY, E_KEY};
#endif

class Character : public Object
{
public:
    Character();
    virtual ~Character();

    // Draw image per frame
    // override virtual function "Object::Draw"
    void Draw();
    // Load bitmaps of animation image into container "moveImg"
    void Load_Move();

    // Update monster position per frame
    // And detect if it reaches end point but not destroyed
    bool Move(bool (&hold)[KeysUsed]);
    void DoAttack(int, int);

    // functions that return informations of monster
    double getRaianCCW() { return radian_ccw; }
    int getWorth() { return worth; }
    int getScore() { return score; }
    int getVx() { return vx; }
    int getVy() { return vy; }

    bool Subtract_HP(int);
    void SetRadianCCW(int, int);
    void SetVx(int);
    void SetVy(int);

protected:
    int HealthPoint = 20;
    int speed = 1;
    int worth = 10;
    int score = 100;
    int state;
    char class_name[20];
    // attck info
    int attack_harm_point = 5;
    int attack_velocity = 10;
    ALLEGRO_BITMAP *attack_img = al_load_bitmap("./Tower/Storm_Beam.png");
    std::vector<Attack*> attack_set;
    //
private:
    double radian_ccw;
    // end point
    int end_x, end_y;
    // animation counter
    int counter;
    // animation image of current direction
    int sprite_pos;
    // VELOCITY
    int vx = 0, vy = 0;

    // set of animation images
    std::vector<ALLEGRO_BITMAP*>    moveImg;
};


#endif // CHARACTER_H_INCLUDED
