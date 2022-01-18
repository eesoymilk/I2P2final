#include "Character.h"
#include <cmath>

Character::Character(int spawn_x, int spawn_y)
{
    circle = new Circle;
    // circle->x = spawn_x * grid_width + grid_width/2;
    // circle->y = spawn_y * grid_height + grid_height/2;
    circle->x = spawn_x;
    circle->y = spawn_y;
    circle->r = grid_width / 2;
    sprite_count = 0;
    counter = 0;
    strncpy(class_name, "Jacket", 20);
    //Load_Img();
}


// Character::~Character()
// {
//     for(unsigned int i = 0; i < moveImg.size(); i++) {
//         ALLEGRO_BITMAP *img = moveImg[i];
//         moveImg.erase(moveImg.begin() + i);
//         i--;
//         al_destroy_bitmap(img);
//     }
//     moveImg.clear();

//     delete circle;
// }

void
Character::Load_Img()
{
    char buffer[50];

    for (int i = 0; i < 5; i++) {
        for(int j = 0; j < sprites[i]; j++) {
            ALLEGRO_BITMAP *img;
            // sprintf(buffer, "./%s/%s_%d.png", class_name, firearm_names[i], j);
            sprintf(buffer, "./Jacket/%s_%d.png", firearm_names[i], j);
            img = al_load_bitmap(buffer);
            if(img) moveImg.push_back(img);
        }
    }
}

void
Character::Draw()
{
    for (unsigned int i = 0; i < this->bullets.size(); i++)
        this->bullets[i]->Draw();

    int offset = 0;
    for (int i = 0; i < firearm; i++)       offset += sprites[i];
    if (!moveImg[offset + sprite_count])    return;

    // get height and width of sprite bitmap
    ALLEGRO_BITMAP* curImg = moveImg[offset + sprite_count];
    int w = al_get_bitmap_width(curImg);
    int h = al_get_bitmap_height(curImg);
    double cx = w / 2, cy = h / 2;
    double angle = 2 * PI - getRadianCCW();
    auto [dx, dy] = Transform();
    //printf("%d %d\n", cam.first, cam.second);
    // printf("Jacket: %d %d %d %d\n", circle->x, circle->y, dx, dy);
    al_draw_scaled_rotated_bitmap(curImg, cx, cy, dx, dy, CharacterScale, CharacterScale, angle, 0);
}

// void
// Character::Move(bool (&move_keys)[5], std::vector<Wall*> WallMap)
// {

//     if (move_keys[LSHIFT_KEY])  max_speed = 5;
//     else                        max_speed = 3;

//     if (move_keys[W_KEY])                    setVy(vy - Acceleration);
//     else if (!move_keys[S_KEY] && vy < 0)    setVy(vy + 1);

//     if (move_keys[A_KEY])                    setVx(vx - Acceleration);
//     else if (!move_keys[D_KEY] && vx < 0)    setVx(vx + 1);

//     if (move_keys[S_KEY])                    setVy(vy + Acceleration);
//     else if (!move_keys[W_KEY] && vy > 0)    setVy(vy - 1);

//     if (move_keys[D_KEY])                    setVx(vx + Acceleration);
//     else if (!move_keys[A_KEY] && vx > 0)    setVx(vx - 1);

//     counter = (counter + 1) % draw_frequency;
//     if (vx == 0 && vy == 0) {
//         sprite_count = 0;
//     } else if (counter == 0) {
//         sprite_count = (sprite_count + 1) % sprites[firearm];
//     }

//     // printf("vx: %d, vy: %d\n", vx, vy);
//     circle->x += vx;
//     circle->y += vy;
//     for(auto wall: WallMap){
//         if(wall->overlap(circle->x, circle->y)){
//             circle->x -= vx;
//             circle->y -= vy;
//             break;
//         }
//     }
// }

Weapon*
Character::DropWeapon()
{
    printf("Start Dropping...\n");
    firearm = 0;
    Weapon* dropped = wielding;
    wielding = NULL;
    printf("Before Dropping...\n");
    if (dropped)    dropped->Drop(circle->x, circle->y);
    printf("Dropped\n");
    return dropped;
}

void
Character::PickWeapon(Weapon* w)
{
    // if (wielding != NULL)   DropWeapon();
    w->Pick();
    wielding = w;
    firearm = w->getType();
}

// void
// Character::FireWeapon(int mouse_x, int mouse_y)
// {
//     Weapon* w = this->getWeapon();
//     if (w != NULL && w->Fire()) {
//         auto [x1, y1] = Transform();
//         // printf("x1 = %d, y1 = %d\n", x1, y1);
//         auto [ux, uy] = UnitVector(mouse_x - x1, mouse_y - y1);
//         // printf("ux = %lf, uy = %lf\n", ux, uy);
//         // Circle* shooter = new Circle(cam.first, cam.second, this->circle->r);
//         printf("Fire!\n");
//         Bullet *b = new Bullet (
//             this->getCircle(),
//             ux, uy,
//             w->getDamage(),
//             w->getSpeed(),
//             w->getBulletImg()
//         );
//         this->bullets.push_back(b);
//     }
// }

bool
Character::TakeDamage(int damage)
{
    if (HP == 0)    return false;
    if (damage >= HP) {
        HP = 0;
        return true;
    }
    else {
        HP -= damage;
        return false;
    }
}

void
Character::EraseBullet(int i)
{
    Bullet* b = bullets[i];
    bullets.erase(bullets.begin() + i);
    delete b;
}

void Character::setRadianCCW(int mouse_x, int mouse_y){
    auto [x0, y0] = Transform();
    double vector_x = mouse_x - x0;
    double vector_y = -(mouse_y - y0);
    double radian = atan(vector_y / vector_x);

    if (vector_x > 0 && vector_y < 0)   radian += 2 * PI;
    if (vector_x < 0)                   radian += PI;
    // printf("vector_x = %lf, vector_y = %lf\n", vector_x, vector_y);
    // printf("degree = %lf\n", radian * 180 / PI);
    radian_ccw = radian;
}

void Character::setVx(int v){
    if (v > max_speed)       vx = max_speed;
    else if (v < -max_speed) vx = -max_speed;
    else                    vx = v;
}

void Character::setVy(int v){
    if (v > max_speed)       vy = max_speed;
    else if (v < -max_speed) vy = -max_speed;
    else                    vy = v;
}
