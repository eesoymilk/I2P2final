#include "Enemy.h"

Enemy::Enemy(int spwan_x, int spwan_y) : Character(spwan_x, spwan_y)
{
    HP = 100;
    sprites[UNARMED] = 7;
    sprites[PISTOL] = 8;
    sprites[SMG] = 8;
    sprites[AR] = 8;

    strncpy(class_name, "Enemy", 20);
    Load_Img();
}

Enemy::~Enemy()
{
    std::vector<ALLEGRO_BITMAP*> moveImg = getImg().first;
    for(unsigned int i = 0; i < moveImg.size(); i++) {
        ALLEGRO_BITMAP *img = moveImg[i];
        moveImg.erase(moveImg.begin() + i);
        i--;
        al_destroy_bitmap(img);
    }
    moveImg.clear();

    delete circle;
}

void
Enemy::Draw()
{   
    for (unsigned int i = 0; i < this->bullets.size(); i++)
        this->bullets[i]->Draw();

    int offset = 0;
    for (int i = 0; i < getFirearm(); i++)       offset += sprites[i];
    // std::vector<ALLEGRO_BITMAP*> moveImg = getImg().first;
    if (!moveImg[offset + getSpriteCnt()])  return;

    // printf("Rendering Image determined.\n");
    // get height and width of sprite bitmap
    ALLEGRO_BITMAP* curImg = moveImg[offset + getSpriteCnt()];
    int w = al_get_bitmap_width(curImg);
    int h = al_get_bitmap_height(curImg);
    double cx = w / 2, cy = h / 2;
    double angle = 2 * PI - getRadianCCW();
    auto [dx, dy] = Transform();
    //printf("%d %d\n", cam.first, cam.second);
    // printf("Enemy: %d %d %d %d\n", circle->x, circle->y, dx, dy);
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