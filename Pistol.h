#ifndef PISTOL_H_INCLUDED
#define PISTOL_H_INCLUDED

#include "Weapon.h"

class Pistol : public Weapon
{
public:
    Pistol() : Weapon()
    {
        char buffer[50];
        type = 1;
        damage = 15;
        fire_rate = 30;
        speed = 10;
        in_magzine = magzine_size = 10;
        reserved_bullets = 60;
        reload_time = 80;
        strncpy(class_name, "PISTOL", 20);
        sprintf(buffer, "./Weapon/%s.png", class_name);
        // printf("Loading Image...\n");
        weaponImg = al_load_bitmap(buffer);
        bulletImg = al_load_bitmap("./Weapon/BULLET.png");
        icon = al_load_bitmap("pistol.png");
        // load Sound
        sample = al_load_sample("pistol.ogg");
        Sound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(Sound, ALLEGRO_PLAYMODE_ONCE);
        al_attach_sample_instance_to_mixer(Sound, al_get_default_mixer());

        sample = al_load_sample("Load.ogg");
        ReloadSound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(ReloadSound, ALLEGRO_PLAYMODE_ONCE);
        al_attach_sample_instance_to_mixer(ReloadSound, al_get_default_mixer());
    }
};
#endif // PISTOL_H_INCLUDED