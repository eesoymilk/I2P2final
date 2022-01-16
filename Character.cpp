#include "Character.h"
#include <cmath>

#define InitX 0
#define InitY 0
#define MaxSpeed 3
#define Acceleration 1
#define SCALE 2

const char  state_name[][10] = {"UNARMED", "PISTOL", "SMG", "AR"};

// set counter frequency of drawing moving animation
const int draw_frequency = 10;

Character::Character(int spawn_x, int spawn_y)
{
    circle = new Circle;
    circle->x = spawn_x * grid_width + grid_width/2;
    circle->y = spawn_y * grid_height + grid_height/2;
    circle->r = grid_width / 2;
    sprite_pos = 0;
    counter = 0;
    strncpy(class_name, "Jacket", 20);
    Load_Img();
}


Character::~Character()
{
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
Character::Load_Img()
{
    char buffer[50];

    for (int i = 0; i < 1; i++) {
        for(int j = 0; j < 7; j++) {
            ALLEGRO_BITMAP *img;
            sprintf(buffer, "./%s/%s_%d.png", class_name, state_name[i], j);
            img = al_load_bitmap(buffer);
            if(img)
                moveImg.push_back(img);
        }
    }
}

void
Character::Draw()
{
    for (unsigned int i = 0; i < this->bullets.size(); i++)
        this->bullets[i]->Draw();

    int offset = 0;
    if (getWeapon())    offset += 7;
    if(!moveImg[offset + sprite_pos])
        return;

    // get height and width of sprite bitmap
    int w = al_get_bitmap_width(moveImg[offset + sprite_pos]);
    int h = al_get_bitmap_height(moveImg[offset + sprite_pos]);

    ALLEGRO_BITMAP* curImg = moveImg[offset + sprite_pos];
    double cx = w / 2, cy = h / 2;
    double angle = 2 * PI - getRadianCCW();
    auto [dx, dy] = Transform();
    //printf("%d %d\n", cam.first, cam.second);
    // printf("Jacket: %d %d %d %d\n", circle->x, circle->y, dx, dy);
    al_draw_scaled_rotated_bitmap(curImg, cx, cy, dx, dy, SCALE, SCALE, angle, 0);
}

bool
Character::Move(bool (&hold)[KeysUsed])
{
    counter = (counter + 1) % draw_frequency;

    if(counter == 0)    sprite_pos = (sprite_pos + 1) % 7;

    // when getting to end point, return true
    if(circle->x == end_x && circle->y == end_y)    return true;

    if (hold[W_KEY])                    setVy(vy - Acceleration);
    else if (!hold[S_KEY] && vy < 0)    setVy(vy + 1);

    if (hold[A_KEY])                    setVx(vx - Acceleration);
    else if (!hold[D_KEY] && vx < 0)    setVx(vx + 1);

    if (hold[S_KEY])                    setVy(vy + Acceleration);
    else if (!hold[W_KEY] && vy > 0)    setVy(vy - 1);

    if (hold[D_KEY])                    setVx(vx + Acceleration);
    else if (!hold[A_KEY] && vx > 0)    setVx(vx - 1);

    // printf("vx: %d, vy: %d\n", vx, vy);
    circle->x += vx;
    circle->y += vy;

    // if not reaching end point, return false
    return false;
}

void
Character::PickWeapon(Weapon* w)
{
    if (wielding != NULL) {
        wielding->Drop(circle->x, circle->y);
    }
    wielding = w;
}

void
Character::DoAttack(int mouse_x, int mouse_y)
{
    Weapon* w = this->getWeapon();
    if (w != NULL && w->isReadyToFire()) {
        w->Fire();
        auto [x1, y1] = Transform();
        // printf("x1 = %d, y1 = %d\n", x1, y1);
        auto [ux, uy] = UnitVector(mouse_x - x1, mouse_y - y1);
        // printf("ux = %lf, uy = %lf\n", ux, uy);
        // Circle* shooter = new Circle(cam.first, cam.second, this->circle->r);
        printf("Fire!\n");
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

bool
Character::Subtract_HP(int harm_point)
{
    HealthPoint -= harm_point;

    return (HealthPoint <= 0);
}

void Character::setRadianCCW(int mouse_x, int mouse_y){
    double vector_x = mouse_x - circle->x;
    double vector_y = -(mouse_y - circle->y);
    double radian = atan(vector_y / vector_x);

    if (vector_x > 0 && vector_y < 0)   radian += 2 * PI;
    if (vector_x < 0)                   radian += PI;
    // printf("vector_x = %lf, vector_y = %lf\n", vector_x, vector_y);
    // printf("degree = %lf\n", radian * 180 / PI);
    radian_ccw = radian;
}

void Character::setVx(int v){
    if (v > MaxSpeed)       vx = MaxSpeed;
    else if (v < -MaxSpeed) vx = -MaxSpeed;
    else                    vx = v;
}

void Character::setVy(int v){
    if (v > MaxSpeed)       vy = MaxSpeed;
    else if (v < -MaxSpeed) vy = -MaxSpeed;
    else                    vy = v;
}