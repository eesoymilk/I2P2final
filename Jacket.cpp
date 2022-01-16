#include "Jacket.h"

const int hud_width = 600;
const int hud_height = 200;
const int font_start = 20;

Jacket::Jacket(int spwan_x, int spwan_y) : Character(spwan_x, spwan_y)
{
    HealthPoint = 20;
    sprites[UNARMED] = 7;
    sprites[PISTOL] = 8;
    sprites[SMG] = 8;
    sprites[AR] = 8;

    hudFont = al_load_ttf_font("pirulen.ttf", font_size, 0); // load font
    strncpy(class_name, "Jacket", 20);
    Load_Img();
}

Jacket::~Jacket()
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
Jacket::Draw()
{
    for (unsigned int i = 0; i < this->bullets.size(); i++)
        this->bullets[i]->Draw();

    int offset = 0;
    for (int i = 0; i < getFirearm(); i++)       offset += sprites[i];
    std::vector<ALLEGRO_BITMAP*> moveImg = getImg().first;
    if (!moveImg[offset + getSpriteCnt()])  return;

    // get height and width of sprite bitmap
    ALLEGRO_BITMAP* curImg = moveImg[offset + getSpriteCnt()];
    int w = al_get_bitmap_width(curImg);
    int h = al_get_bitmap_height(curImg);
    double cx = w / 2, cy = h / 2;
    double angle = 2 * PI - getRadianCCW();
    auto [dx, dy] = Transform();
    //printf("%d %d\n", cam.first, cam.second);
    // printf("Jacket: %d %d %d %d\n", circle->x, circle->y, dx, dy);
    al_draw_scaled_rotated_bitmap(curImg, cx, cy, dx, dy, CharacterScale, CharacterScale, angle, 0);

    Weapon* weapon = getWeapon();
    int ammo = 0, mag_size = 0, reserved = 0;
    if (weapon) {
        ammo = weapon->getAmmo();
        mag_size = weapon->getMagSize();
        reserved = weapon->getReserved();
    }

    switch(getFirearm()){
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

    char buffer[50];
    sprintf(buffer, "%d", HealthPoint);
    int alpha = 128; // half translucent
    //al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgba(255, 255, 255, alpha));
    //al_draw_bitmap(bmp, 0, 0, 0);
    al_draw_filled_rectangle(0, window_height - hud_height, hud_width, window_height, al_map_rgb(0, 0, 0));
    al_draw_text(hudFont, al_map_rgb(255, 255, 255), font_size, window_height - hud_height + font_start, 0, buffer);
    double length = (hud_width - font_start - 4 * font_size) * HealthPoint / 100.0;
    al_draw_filled_rectangle(4 * font_size, window_height - hud_height + font_start, 4 * font_size + (int)length, window_height - hud_height + font_start + font_size, al_map_rgb(255, 0, 0));
    sprintf(buffer, "%d/%d   %d", ammo, mag_size, reserved);
    al_draw_text(hudFont, al_map_rgb(255, 255, 255), font_start, window_height - font_start - 3 * font_size / 2, 0, buffer);
    w = al_get_bitmap_width(icon); h = al_get_bitmap_height(icon);
    al_draw_bitmap(icon, hud_width - w - font_size, window_height - h - font_start, 0);
}
