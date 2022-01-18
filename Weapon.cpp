#include "Weapon.h"

#define InitX 0
#define InitY 0
#define MaxSpeed 3
#define Acceleration 1
#define PI 3.1415926
#define SCALE 2

Weapon::Weapon()
{
    circle = new Circle;
    circle->r = 2 * grid_width;
    dropped = false;
    strncpy(class_name, "Weapon", 20);
}


Weapon::~Weapon()
{
    al_destroy_bitmap(weaponImg);
    al_destroy_bitmap(bulletImg);
    al_destroy_sample(sample);
    for(unsigned int i = 0; i < FiringSound.size(); i++) {
        ALLEGRO_SAMPLE_INSTANCE *instance = FiringSound[i];
        FiringSound.erase(FiringSound.begin() + i);
        i--;
        al_destroy_sample_instance(instance);
    }
    al_destroy_sample_instance(LoadSound);
    al_destroy_sample_instance(ReloadSound);
    delete circle;
}

void
Weapon::LoadData()
{
    char buffer[50];
    
    // load images
    sprintf(buffer, "./Weapon/%s.png", class_name);
    weaponImg = al_load_bitmap(buffer);
    bulletImg = al_load_bitmap("./Weapon/BULLET.png");

    // load Sound
    sprintf(buffer, "./SoundEffect/%s_FIRING.wav", class_name);
    sample = al_load_sample(buffer);
    for (int i = 0; i < 30; i++) {
        FiringSound.push_back(al_create_sample_instance(sample));
        al_set_sample_instance_playmode(FiringSound[i], ALLEGRO_PLAYMODE_ONCE);
        al_attach_sample_instance_to_mixer(FiringSound[i], al_get_default_mixer());
    }

    sprintf(buffer, "./SoundEffect/%s_LOADED.wav", class_name);
    sample = al_load_sample(buffer);
    LoadSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(LoadSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(LoadSound, al_get_default_mixer());

    sprintf(buffer, "./SoundEffect/%s_RELOADING.wav", class_name);
    sample = al_load_sample(buffer);
    ReloadSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(ReloadSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(ReloadSound, al_get_default_mixer());
}

void
Weapon::Draw()
{
    if (dropped) {
        // printf("Drawing weapon...\n");
        // get height and width of sprite bitmap
        int w = al_get_bitmap_width(weaponImg);
        int h = al_get_bitmap_height(weaponImg);
        // printf("Image's data gotten.\n");

        // draw bitmap align grid edge
        // double dx = circle->x - w / 2, dy = circle->y - h / 2;
        // printf("Transforming...\n");
        auto [dx, dy] = Transform();
        // printf("cam_x = %d, cam_y = %d\n", cam.first, cam.second);
        al_draw_bitmap(weaponImg, dx, dy, 0);
        // printf("Drawn weapon.\n");
    }
}

void
Weapon::Pick()
{
    // PICKING UP WEAPON SOUND EFFECT
    fire_counter = 0;
    dropped = false;
}

void
Weapon::Drop(int drop_x, int drop_y)
{
    // DROPPING WEAPON SOUND EFFECT
    // printf("circle->x = %d, circle->y = %d\n", circle->x, circle->y);
    // printf("drop_x = %d, drop_y = %d\n", drop_x, drop_y);
    circle->x = drop_x;
    circle->y = drop_y;
    dropped = true;
    // printf("Dropped\n");
}

bool
Weapon::Fire()
{
    static int cnt = 0;
    if (fire_counter < fire_rate)   return false;
    if (in_magzine <= 0) {
        // DRY MAG SOUND EFFECT
        return false;
    }
    in_magzine--;
    fire_counter = 0;
    if (cnt++ == 29)  cnt = 0;
    al_play_sample_instance(FiringSound[cnt]); // FIRING SOUND EFFECT
    return true;
}

void
Weapon::StartReload()
{
    // printf("Start to Reload!\n");
    if (reserved_bullets == 0) {
        // RELOAD BUT NO AMMO SOUND EFFECT
        return;
    }
    if (in_magzine == magzine_size) {
        // RELOAD BUT FULL MAG EFFECT
        return;
    }
    al_play_sample_instance(ReloadSound);// RELOADING SOUND EFFECT
    reloading = true;
    reload_counter = 0;
    return;
}

void
Weapon::Reload()
{
    // printf("Reloading!\n");
    // printf("%d / %d\n", reload_counter, reload_time);
    if (reload_counter < reload_time) {
        reload_counter++;
        return;
    }
    al_play_sample_instance(LoadSound);   // LOADED SOUND EFFECT
    int to_reload = magzine_size - in_magzine;
    if (reserved_bullets >= to_reload) {
        reserved_bullets -= to_reload;
        in_magzine = magzine_size;
    } else {
        in_magzine += reserved_bullets;
        reserved_bullets = 0;
    }
    fire_counter = 0;
    reloading = false;
    return;
}
