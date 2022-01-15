#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include "Object.h"
#include "Circle.h"
#include "global.h"

#ifndef DIRECTION_OBJECT
#define DIRECTION_OBJECT
enum {LEFT=0, RIGHT, UP, DOWN};
#endif

#ifndef KEYS
#define KeysUsed 5
#define KEYS
enum {W_KEY=0, A_KEY, S_KEY, D_KEY, E_KEY};
#endif


class Character: public Object {
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

    // functions that return informations of monster
    int getDir() { return direction; }
    int getWorth() { return worth; }
    int getScore() { return score; }
    int getVx() { return vx; }
    int getVy() { return vy; }

    bool Subtract_HP(int);
    void SetVx(int);
    void SetVy(int);

protected:
    int direction_count[4];
    int HealthPoint = 20;
    int speed = 1;
    int worth = 10;
    int score = 100;
    char class_name[20];
private:
    int direction;
    // end point
    int end_x, end_y;
    // animation counter
    int counter;
    // animation image of current direction
    int sprite_pos;
    // VELOCITY
    int vx = 0, vy = 0;

    // set of animation images
    std::vector<ALLEGRO_BITMAP*> moveImg;

};


#endif // CHARACTER_H_INCLUDED
