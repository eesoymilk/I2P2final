#include "Menu.h"

const int ThumbWidth = 50;
const int ThumbHeight = 50;
const int gapX = 40, gapY = 30;
const int offsetX = 30 + field_width, offsetY = 150;
const int Initial_Health = 1;
const int Initial_Coin = 10;

const int menu_width = 600;
const int menu_height = 300;
const int font_start = 20;

bool
Menu::isInRange(int point, int startPos, int length)
{
    if(point >= startPos && point <= startPos + length)
        return true;

    return false;
}

Menu::Menu()
{
    char filename[50];

    HealthPoint = 0;
    Ammo = 0;
    reserved_Ammo = 0;

    //menu = al_load_bitmap("./Menu.png");

    menuFont = al_load_ttf_font("pirulen.ttf", font_size, 0); // load font
    icon = al_load_bitmap("./unarmed_icon.png");
}

Menu::~Menu()
{
    //al_destroy_bitmap(menu);
    al_destroy_font(menuFont);
    al_destroy_bitmap(icon);

    /*for(int i=0; i < Num_TowerType; i++)
        al_destroy_bitmap(menu_tower[i]);

    menu_tower.clear();*/
}

void
Menu::Reset()
{
    char filename[50];

    HealthPoint = 0;
    Magzine_size = 0;
    Ammo = 0;
    reserved_Ammo = 0;
    icon = al_load_bitmap("./unarmed_icon.png");

    //menu = al_load_bitmap("./Menu.png");

    //menuFont = al_load_ttf_font("pirulen.ttf", font_size, 0); // load font
}

void
Menu::Update(int health, int ammo, int magzine_size, int reserved_ammo, int type)
{
    HealthPoint = health;
    Ammo = ammo;
    Magzine_size = magzine_size;
    reserved_Ammo = reserved_ammo;
    switch(type){
        case 0:
            icon = al_load_bitmap("./unarmed_icon.png");
            break;
        case 1:
            icon = al_load_bitmap("./Pistol_icon.png");
            break;
        case 2:
            icon = al_load_bitmap("./SMG_icon.png");
            break;
        case 3:
            icon = al_load_bitmap("./AR_icon.png");
            break;
    }
}

void
Menu::Draw()
{
    char buffer[50];
    sprintf(buffer, "%d", HealthPoint);
    int alpha = 128; // half translucent
    //al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba(255, 255, 255, 255));
    al_draw_filled_rectangle(0, window_height - menu_height, menu_width, window_height, al_map_rgb(0, 0, 0));
    al_draw_text(menuFont, al_map_rgb(255, 255, 255), 20, window_height - menu_height + font_start, 0, "Health: ");
    al_draw_text(menuFont, al_map_rgb(255, 255, 255), window_width - menu_width + font_start, font_start + 2 * font_size, 0, buffer);
    al_draw_text(menuFont, al_map_rgb(255, 255, 255), window_width - menu_width + font_start, font_start + 4 * font_size, 0, "Ammo: ");
    sprintf(buffer, "%d/%d %d", Ammo, Magzine_size, reserved_Ammo);
    al_draw_text(menuFont, al_map_rgb(255, 255, 255), window_width - menu_width + font_start, font_start + 6 * font_size, 0, buffer);
    al_draw_bitmap(icon, 0, window_height - menu_height, 0);
    /*char buffer[50];

    sprintf(buffer, "%d", HealthPoint);
    al_draw_bitmap(love, offsetX, 20, 0);
    al_draw_text(menuFont, al_map_rgb(255, 255, 255), 2*al_get_bitmap_width(love) + offsetX, 20, 0, buffer);

    sprintf(buffer, "Coin: %d", Coin);
    al_draw_text(menuFont, al_map_rgb(255, 255, 255), offsetX, 20 + gapY, 0, buffer);

    sprintf(buffer, "Score: %d", Score);
    al_draw_text(menuFont, al_map_rgb(255, 255, 255), offsetX, 20 + 2*gapY, 0, buffer);

    for(int i=0; i < Num_TowerType; i++)
    {
        int pos_x = offsetX + (ThumbWidth + gapX) * (i % 2);
        int pos_y = offsetY + (ThumbHeight + gapY) * (i / 2);

        al_draw_bitmap(menu_tower[i], pos_x, pos_y, 0);
        if(!Enough_Coin(i))
            al_draw_filled_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgba(100, 100, 100, 100));
        else if(i == selectedTower)
            al_draw_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgb(255, 0, 0), 0);
        else
            al_draw_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgb(255, 255, 255), 0);
    }*/
}


