#include "Bullet.h"

Bullet::Bullet(Circle *shooter, double ux, double uy, int damage, int speed, ALLEGRO_BITMAP* bulletImg)
: unit_x(ux), unit_y(uy), damage(damage), speed(speed), bulletImg(bulletImg)
{
    this->pos_x = shooter->x;
    this->pos_y = shooter->y;
    this->circle = new Circle(shooter->x, shooter->y, 10);

    double radian = atan(-uy / ux);
    if (ux > 0 && uy < 0)   radian += 2 * PI;
    if (ux < 0)             radian += PI;
    radian_ccw = radian;
    // initialize the effect sound of attack
    sample = al_load_sample("Arrow.wav");
    arrow = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(arrow, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(arrow, al_get_default_mixer());
    al_set_sample_instance_gain(arrow, Bullet::volume);
    al_play_sample_instance(arrow);
}

Bullet::~Bullet()
{
    delete circle;
    al_destroy_sample_instance(arrow);
    al_destroy_sample(sample);
}

void
Bullet::Move()
{
    // printf("speed = %d, ux = %lf, uy = %lf\n", speed, unit_x, unit_y);
    pos_x += speed * unit_x;
    pos_y += speed * unit_y;
    // printf("x = %d, x = %lf\n", pos_x, pos_y);
    circle->x = (int)pos_x;
    circle->y = (int)pos_y;
}

void
Bullet::Draw()
{
    // get height and width of sprite bitmap
    int w = al_get_bitmap_width(bulletImg);
    int h = al_get_bitmap_height(bulletImg);
    double cx = w / 2, cy = h / 2;
    double angle = 2 * PI - getRadianCCW();
    // printf("angle = %lf\n", angle);
    double dx = circle->x - w / 2, dy = circle->y - h / 2;
    // printf("%d %d\n", dx, dy);
    // printf("Jacket: %d %d %d %d\n", circle->x, circle->y, dx, dy);
    std::pair<int, int> cam = Transform();
    al_draw_scaled_rotated_bitmap(bulletImg, cx, cy, cam.first, cam.second, 1, 1, angle, 0);
    //al_draw_filled_circle(pos_x, pos_y, circle->r, al_map_rgba(196, 79, 79, 200));
}