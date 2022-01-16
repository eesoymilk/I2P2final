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
#include "Weapon.h"
#include "Bullet.h"
#include "global.h"

#ifndef KEYS
#define KEYS
#define KeysUsed 5
enum {W_KEY=0, A_KEY, S_KEY, D_KEY, E_KEY};
#endif

class Character : public Object
{
public:
    Character(int, int);
    virtual ~Character();

    // Draw image per frame
    // override virtual function "Object::Draw"
    void Draw();
    // Load bitmaps of animation image into container "moveImg"
    void Load_Img();

    // Update monster position per frame
    // And detect if it reaches end point but not destroyed
    bool Move(bool (&hold)[KeysUsed]);
    void PickWeapon(Weapon*);
    void DoAttack(int, int);

    // functions that return informations of monster
    Weapon* getWeapon() { return wielding; }
    std::vector<Bullet*> getBullets() { return bullets; }
    double getRadianCCW() { return radian_ccw; }
    int getVx() { return vx; }
    int getVy() { return vy; }
    int getHealth() { return HealthPoint; }

    bool Subtract_HP(int);
    void setRadianCCW(int, int);
    void setVx(int);
    void setVy(int);

protected:
    int HealthPoint = 20;
    char class_name[20];
    std::vector<Bullet*> bullets;
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
    std::vector<ALLEGRO_BITMAP*>    attackImg;
    Weapon *wielding = NULL;
};


#endif // CHARACTER_H_INCLUDED
