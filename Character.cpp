#include "Character.h"
#include <cmath>

#define InitX 0
#define InitY 0
#define MaxSpeed 3
#define Acceleration 1
#define PI 3.1415926

const char  state_name[][10] = {"DEFAULT", "HANDGUN", "RIFLE"};

// set counter frequency of drawing moving animation
const int draw_frequency = 10;

Character::Character()
{
    circle = new Circle;
    circle->x = InitX * grid_width + grid_width/2;
    circle->y = InitY * grid_height + grid_height/2;
    circle->r = grid_width/2;

    // direction_count[] = 5;
    // direction_count[RIGHT] = 5;
    // direction_count[UP] = 4;
    // direction_count[DOWN] = 4;

    sprite_pos = 0;
    counter = 0;
    strncpy(class_name, "Character", 20);
    Load_Move();
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
Character::Load_Move()
{
    char buffer[50];

    for (int i = 0; i < 4; i++) {
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
    int w, h;
    int offset = 0;

    // calculate the number of pictures before current direction
    for(int i = 0; i < state; i++)  offset += 7;

    if(!moveImg[offset + sprite_pos])
        return;

    // get height and width of sprite bitmap
    w = al_get_bitmap_width(moveImg[offset + sprite_pos]);
    h = al_get_bitmap_height(moveImg[offset + sprite_pos]);

    // draw bitmap align grid edge
    al_draw_rotated_bitmap(moveImg[offset + sprite_pos], w / 2, h / 2, circle->x - w / 2, circle->y - h / 2, 2 * PI - getRaianCCW(), 0);

    //al_draw_filled_circle(circle->x, circle->y, circle->r, al_map_rgba(196, 79, 79, 200));
    for (unsigned int i=0; i < this->attack_set.size(); i++)
        this->attack_set[i]->Draw();
}
bool
Character::Move(bool (&hold)[KeysUsed])
{
    counter = (counter + 1) % draw_frequency;

    if(counter == 0)    sprite_pos = (sprite_pos + 1) % 7;

    // when getting to end point, return true
    if(circle->x == end_x && circle->y == end_y)    return true;

    if (hold[W_KEY])                    SetVy(vy - Acceleration);
    else if (!hold[S_KEY] && vy < 0)    SetVy(vy + 1);

    if (hold[A_KEY])                    SetVx(vx - Acceleration);
    else if (!hold[D_KEY] && vx < 0)    SetVx(vx + 1);

    if (hold[S_KEY])                    SetVy(vy + Acceleration);
    else if (!hold[W_KEY] && vy > 0)    SetVy(vy - 1);

    if (hold[D_KEY])                    SetVx(vx + Acceleration);
    else if (!hold[A_KEY] && vx > 0)    SetVx(vx - 1);

    // printf("vx: %d, vy: %d\n", vx, vy);
    circle->x += vx;
    circle->y += vy;

    // if (vx > 0)         vx--;
    // else if (vx < 0)    vx++;
    // if (vy > 0)         vy--;
    // else if (vy < 0)    vy++;

    // if not reaching end point, return false
    return false;
}

void
Character::DoAttack(int mouse_x, int mouse_y)
{
    printf("Attack!\n");
    Attack *attack = new Attack (
        this->circle,
        mouse_x, mouse_y,
        this->attack_harm_point,
        this->attack_velocity,
        this->attack_img
    );
    this->attack_set.push_back(attack);
}

bool
Character::Subtract_HP(int harm_point)
{
    HealthPoint -= harm_point;

    return (HealthPoint <= 0);
}

void Character::SetRadianCCW(int mouse_x, int mouse_y){
    double vector_x = mouse_x - circle->x;
    double vector_y = mouse_y - circle->y;
    double radian = atan(vector_x / vector_y);

    if (vector_x > 0 && vector_y < 0)   radian += 2 * PI;
    if (vector_x < 0)                   radian += PI;

    radian_ccw = radian;
}

// void Character::SetRadianCCW(int mouse_x, int mouse_y){
//     mouse_x -= circle->x;
//     mouse_y -= circle->y;
//     if (mouse_x > mouse_y) 
//         if (mouse_x > -mouse_y) direction = RIGHT;
//         else                    direction = UP;
//     else
//         if (mouse_x > -mouse_y) direction = DOWN;
//         else                    direction = LEFT;
// }

void Character::SetVx(int v){
    if (v > MaxSpeed)       vx = MaxSpeed;
    else if (v < -MaxSpeed) vx = -MaxSpeed;
    else                    vx = v;
}

void Character::SetVy(int v){
    if (v > MaxSpeed)       vy = MaxSpeed;
    else if (v < -MaxSpeed) vy = -MaxSpeed;
    else                    vy = v;
}