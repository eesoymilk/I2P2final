#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

// #ifndef KEYS
// #define KEYS
// #define DirKeysUsed 4
// enum {W_KEY=0, A_KEY, S_KEY, D_KEY};
// #define GameKeysUsed 3
// enum {E_KEY = 0, R_KEY, G_KEY};
// #define FuncKeysUsed 4
// enum {ENTER_KEY=0, P_KEY, H_KEY, ESCAPE_KEY};
// #endif

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

enum {UNARMED = 0, PISTOL, SMG, AR};

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
    bool Move(bool(&hold)[4]);
    void DropWeapon();
    void PickWeapon(Weapon*);
    void FireWeapon(int, int);

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
    int sprites[4];
    std::vector<Bullet*> bullets;
    //
private:
    double radian_ccw;
    // end point
    int end_x, end_y;
    // animation counter
    int firearm = 0, counter;
    // animation image of current direction
    int sprite_count;
    // VELOCITY
    int vx = 0, vy = 0;

    // set of animation images
    std::vector<ALLEGRO_BITMAP*>    moveImg;
    std::vector<ALLEGRO_BITMAP*>    attackImg;
    Weapon *wielding = NULL;
};


#endif // CHARACTER_H_INCLUDED
