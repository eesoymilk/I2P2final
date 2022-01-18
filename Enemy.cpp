#include "Enemy.h"

Enemy::Enemy(int spawn_x, int spawn_y) : Character(spawn_x, spawn_y)
{
    HP = 100;
    pos_x = spawn_x;
    pos_y = spawn_y;
    sprites[UNARMED] = 7;
    sprites[PISTOL] = 8;
    sprites[SMG] = 8;
    sprites[AR] = 8;
    sprites[DEAD] = 7;

    strncpy(class_name, "Enemy", 20);
    Load_Img();
}

Enemy::~Enemy()
{
    for(unsigned int i = 0; i < moveImg.size(); i++) {
        ALLEGRO_BITMAP *img = moveImg[i];
        moveImg.erase(moveImg.begin() + i);
        i--;
        al_destroy_bitmap(img);
    }
    moveImg.clear();
    for(unsigned int i = 0; i < attackImg.size(); i++) {
        ALLEGRO_BITMAP *img = attackImg[i];
        attackImg.erase(attackImg.begin() + i);
        i--;
        al_destroy_bitmap(img);
    }
    attackImg.clear();
    for (auto b : bullets)  delete b;
    bullets.clear();
    if (wielding)   delete wielding;
    delete circle;
    printf("Enemy Deleted!\n");
}

void
Enemy::Move(double ux, double uy, std::vector<Wall*> WallMap)
{
    max_speed = 3;
    
    if (ux || uy)   setSpeed(speed + 1);
    else            setSpeed(speed - 1);

    bool move_x = true, move_y = true, move_both = true;
    for(auto wall: WallMap){
        if (wall->overlap((int)(pos_x + ux * speed), (int)(pos_y + uy * speed))){
            move_both = false;
        } if (wall->overlap((int)(pos_x + ux * speed), circle->y)) {
            move_x = false;
        } if (wall->overlap(circle->x, (int)(pos_y + uy * speed))) {
            move_y = false;
        }
    }
    if (move_both){
        pos_x += ux * speed;
        pos_y += uy * speed;
    }
    else if (move_x) pos_x += ux * speed;
    else if (move_y) pos_y += uy * speed;

    circle->x = (int)pos_x;
    circle->y = (int)pos_y;
}

void
Enemy::FireWeapon(double ux, double uy)
{
    Weapon* w = this->getWeapon();
    if (w->Fire()) {
        // printf("Enemy Fired!\n");
        Bullet *b = new Bullet (
            this->getCircle(),
            ux, uy,
            w->getDamage(),
            w->getSpeed(),
            w->getBulletImg()
        );
        this->bullets.push_back(b);
    }
}

void
Enemy::Assault(int jx, int jy, std::vector<Wall*> WallMap)
{
    // printf("I see you...\n");
    auto [ux, uy] = UnitVector(jx - getX(), jy - getY());
    setRadianCCW(jx, jy);
    if (Distance(jx, jy) > 500) {
        Move(ux, uy, WallMap);
    }
    if (wielding) {
        if (wielding->getReserved()) {
            // printf("Enemy is about to fire.\n");
            if (wielding->getAmmo() > 0)        FireWeapon(ux, uy);
            else if (!wielding->isReloading())  wielding->StartReload();
        }
    }
}

void
Enemy::Draw()
{   
    int w, h, offset = 0;
    ALLEGRO_BITMAP* curImg;

    for (unsigned int i = 0; i < this->bullets.size(); i++) {
        // printf("Drawing Enemy's Bullet...\n");
        this->bullets[i]->Draw();
    }

    if (HP) {
        for (int i = 0; i < getFirearm(); i++)       offset += sprites[i];
        if (!moveImg[offset + getSpriteCnt()])  return;
        curImg = moveImg[offset + getSpriteCnt()];
    } else {
        for (int i = 0; i < 4; i++) offset += sprites[i];
        offset += (int)(getRadianCCW() * 180 / PI) % sprites[4];
        curImg = moveImg[offset + getSpriteCnt()];
    }
    w = al_get_bitmap_width(curImg);
    h = al_get_bitmap_height(curImg);
    double cx = w / 2, cy = h / 2;
    double angle = 2 * PI - getRadianCCW();
    auto [dx, dy] = Transform();
    al_draw_scaled_rotated_bitmap(curImg, cx, cy, dx, dy, CharacterScale, CharacterScale, angle, 0);
}

void Enemy::setRadianCCW(int t_x, int t_y)
{
    double vector_x = t_x - circle->x;
    double vector_y = -(t_y - circle->y);
    double radian = atan(vector_y / vector_x);

    if (vector_x > 0 && vector_y < 0)   radian += 2 * PI;
    if (vector_x < 0)                   radian += PI;
    // printf("vector_x = %lf, vector_y = %lf\n", vector_x, vector_y);
    // printf("degree = %lf\n", radian * 180 / PI);
    radian_ccw = radian;
}

void Enemy::setSpeed(int v) {
    if (v >= 0 && v <= max_speed)   speed = v;
}
