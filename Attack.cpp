#include "Attack.h"

const int Velocity[] = {8, 8, 6, 10, 20};
const int Harm[] = {5, 7, 15, 3, 5};

Attack::Attack(Circle *attacker, int mx, int my, int harm_point, int velocity, ALLEGRO_BITMAP* attack_img)
{
    float vector_x = mx - attacker->x;
    float vector_y = my - attacker->y;
    float len = sqrt(vector_x * vector_x + vector_y * vector_y);

    // initialize the information of attack
    this->pos_x = attacker->x;
    this->pos_y = attacker->y;
    this->circle = new Circle(attacker->x, attacker->y, 10);

    this->direction_x = vector_x / len;
    this->direction_y = vector_y / len;

    this->attack_velocity = velocity;
    this->harm_point = harm_point;
    this->attack_img = attack_img;

    // initialize the effect sound of attack
}

Attack::~Attack()
{
    delete circle;
    al_destroy_sample_instance(arrow);
    al_destroy_sample(sample);
}

void
Attack::Draw()
{
    al_draw_bitmap(attack_img, pos_x - circle->r, pos_y - circle->r, 0);
    pos_x += attack_velocity * direction_x;
    pos_y += attack_velocity * direction_y;

    circle->x = (int)pos_x;
    circle->y = (int)pos_y;

    //al_draw_filled_circle(pos_x, pos_y, circle->r, al_map_rgba(196, 79, 79, 200));
}

