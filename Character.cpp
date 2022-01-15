#include "Character.h"

#define InitX 0
#define InitY 0
#define MaxSpeed 3
#define Acceleration 1

const int axis_x[] = {-1, 1, 0, 0};
const int axis_y[] = {0, 0, -1, 1};
const char direction_name[][10] = {"LEFT", "RIGHT", "UP", "DOWN"};

// set counter frequency of drawing moving animation
const int draw_frequency = 10;

Character::Character()
{
    // default direction is right
    direction = RIGHT;

    circle = new Circle;
    circle->x = InitX * grid_width + grid_width/2;
    circle->y = InitY * grid_height + grid_height/2;
    circle->r = grid_width/2;

    direction_count[LEFT] = 1;
    direction_count[RIGHT] = 1;
    direction_count[UP] = 1;
    direction_count[DOWN] = 1;

    sprite_pos = 0;
    counter = 0;
    strncpy(class_name, "Wolf", 20);
    Load_Move();
}


Character::~Character()
{
    for(unsigned int i=0; i<moveImg.size(); i++)
    {
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

    for(int i=0; i < 4; i++)
    {
        for(int j=0; j<direction_count[i]; j++)
        {
            ALLEGRO_BITMAP *img;
            sprintf(buffer, "./%s/%s_%d.png", class_name, direction_name[i], j);

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
    for(int i=0; i<direction; i++)
        offset += direction_count[i];

    if(!moveImg[offset + sprite_pos])
        return;

    // get height and width of sprite bitmap
    w = al_get_bitmap_width(moveImg[offset + sprite_pos]);
    h = al_get_bitmap_height(moveImg[offset + sprite_pos]);

    // draw bitmap align grid edge
    al_draw_bitmap(moveImg[offset + sprite_pos], circle->x - w/2, circle->y - (h - grid_height/2), 0);

    //al_draw_filled_circle(circle->x, circle->y, circle->r, al_map_rgba(196, 79, 79, 200));
}
bool
Character::Move()
{
    counter = (counter + 1) % draw_frequency;

    if(counter == 0)
        sprite_pos = (sprite_pos + 1) % direction_count[direction];

    // when getting to end point, return true
    if(circle->x == end_x && circle->y == end_y)
        return true;

    if (hold[W_KEY])                    SetVy(vy - Acceleration);
    else if (!hold[S_KEY] && vy < 0)    SetVy(vy + 1);

    if (hold[A_KEY])                    SetVx(vx - Acceleration);
    else if (!hold[D_KEY] && vx < 0)    SetVx(vx + 1);

    if (hold[S_KEY])                    SetVy(vy + Acceleration);
    else if (!hold[W_KEY] && vy > 0)    SetVy(vy - 1);

    if (hold[D_KEY])                    SetVx(vx + Acceleration);
    else if (!hold[A_KEY] && vx > 0)    SetVx(vx - 1);

    circle->x += vx;
    circle->y += vy;

    // if (vx > 0)         vx--;
    // else if (vx < 0)    vx++;
    // if (vy > 0)         vy--;
    // else if (vy < 0)    vy++;

    // if not reaching end point, return false
    return false;
}

bool
Character::Subtract_HP(int harm_point)
{
    HealthPoint -= harm_point;

    return (HealthPoint <= 0);
}

void Character::TuggleHold(int k) {
    if (hold[k] == true)    hold[k] = false;
    else                    hold[k] = true;
}

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

