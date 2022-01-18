#ifndef ASSAULT_RIFLE_H_INCLUDED
#define ASSAULT_RIFLE_H_INCLUDED

#include "Weapon.h"

class AssaultRifle : public Weapon
{
public:
    AssaultRifle() : Weapon()
    {
        char buffer[50];
        type = 3;
        damage = 19;
        fire_rate = 6;
        speed = 10;
        in_magzine = magzine_size = 30;
        reserved_bullets = 120;
        reload_time = 80;
        strncpy(class_name, "AR", 20);
        sprintf(buffer, "./Weapon/%s.png", class_name);
        printf("Loading AR Image...\n");
        weaponImg = al_load_bitmap(buffer);
        bulletImg = al_load_bitmap("./Weapon/BULLET.png");
        // load Sound
        sample = al_load_sample("AR_FIRING.ogg");
        Sound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(Sound, ALLEGRO_PLAYMODE_ONCE);
        al_attach_sample_instance_to_mixer(Sound, al_get_default_mixer());

        sample = al_load_sample("AR_LAODING.ogg");
        LoadSound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(Sound, ALLEGRO_PLAYMODE_ONCE);
        al_attach_sample_instance_to_mixer(Sound, al_get_default_mixer());

        sample = al_load_sample("AR_RELOADING.ogg");
        ReloadSound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(ReloadSound, ALLEGRO_PLAYMODE_ONCE);
        al_attach_sample_instance_to_mixer(ReloadSound, al_get_default_mixer());
    }
    ~AssaultRifle() { printf("Deleting AR...\n"); }
};
#endif // ASSAULT_RIFLE_H_INCLUDED
