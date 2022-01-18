#ifndef SUBMACHINE_GUN_H_INCLUDED
#define SUBMACHINE_GUN_H_INCLUDED

#include "Weapon.h"

class SubmachineGun : public Weapon
{
public:
    SubmachineGun() : Weapon()
    {
        char buffer[50];
        type = 2;
        damage = 9;
        fire_rate = 4;
        speed = 10;
        in_magzine = magzine_size = 30;
        reserved_bullets = 150;
        reload_time = 80;
        strncpy(class_name, "SMG", 20);
        sprintf(buffer, "./Weapon/%s.png", class_name);
        printf("Loading SMG Image...\n");
        weaponImg = al_load_bitmap(buffer);
        bulletImg = al_load_bitmap("./Weapon/BULLET.png");
        // load Sound
        sample = al_load_sample("SMG_FIRING.ogg");
        Sound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(Sound, ALLEGRO_PLAYMODE_ONCE);
        al_attach_sample_instance_to_mixer(Sound, al_get_default_mixer());

        sample = al_load_sample("SMG_LAODING.ogg");
        LoadSound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(Sound, ALLEGRO_PLAYMODE_ONCE);
        al_attach_sample_instance_to_mixer(Sound, al_get_default_mixer());

        sample = al_load_sample("SMG_RELOADING.ogg");
        ReloadSound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(ReloadSound, ALLEGRO_PLAYMODE_ONCE);
        al_attach_sample_instance_to_mixer(ReloadSound, al_get_default_mixer());
    }
};
#endif // SUBMACHINE_GUN_H_INCLUDED
