#include "Enemy.h"

Enemy::Enemy(int spwan_x, int spwan_y) : Character(spwan_x, spwan_y)
{
    HP = 100;
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

    delete circle;
}

void
Enemy::Draw()
{   
    int w, h, offset = 0;
    ALLEGRO_BITMAP* curImg;

    for (unsigned int i = 0; i < this->bullets.size(); i++)
        this->bullets[i]->Draw();

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

void Enemy::setRadianCCW(int t_x, int t_y){
    double vector_x = t_x - circle->x;
    double vector_y = -(t_y - circle->y);
    double radian = atan(vector_y / vector_x);

    if (vector_x > 0 && vector_y < 0)   radian += 2 * PI;
    if (vector_x < 0)                   radian += PI;
    // printf("vector_x = %lf, vector_y = %lf\n", vector_x, vector_y);
    // printf("degree = %lf\n", radian * 180 / PI);
    radian_ccw = radian;
}