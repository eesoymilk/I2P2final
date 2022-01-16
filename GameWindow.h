#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <list>
#include <time.h>
#include "Menu.h"
#include "Level.h"
#include "Bullet.h"
#include "Slider.h"

// EDITED
#include "Jacket.h"
#include "Pistol.h"
#include "SubmachineGun.h"
#include "AssaultRifle.h"
//

#define GAME_EXIT -1
#define GAME_CONTINUE 0
#define GAME_NEXT 1
#define GAME_STOP 2

#define GAMESTATE_MENU      0
#define GAMESTATE_INGAME    1
#define GAMESTATE_TUTORIAL  2
#define GAMESTATE_PAUSE     3
#define GAMESTATE_END       4

#define MaxSpeed 3
#define Acceleration 1

// clock rate
const float FPS = 60;

// total number of level
const int LevelNum = 4;

// 1 coin every 2 seconds
const int CoinSpeed = FPS * 2;
const int Coin_Time_Gain = 1;

class GameWindow
{
public:
    // constructor
    GameWindow();
    // each process of scene
    void game_init();
    void game_reset();
    void game_play();
    void game_begin();
    void game_menu();

    int game_run();
    int game_update();

    void show_err_msg(int msg);
    void game_destroy();

    // each drawing scene function
    void draw_running_map();
    void draw_startscene();
    void Draw();

    // process of updated event
    int process_event();
    // detect if mouse hovers over a rectangle
    bool mouse_hover(int, int, int, int);

    // Tower* create_tower(int);
    // Monster* create_monster();
    Character* spawnCharacter(int, int, int);
    Weapon* spawnWeapon(int, int, int);

public:
    bool initial = true;

private:
    ALLEGRO_BITMAP *icon;
    ALLEGRO_BITMAP *tower[Num_TowerType];
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_BITMAP *startscene = NULL;
    ALLEGRO_BITMAP *helpscene = NULL;
    ALLEGRO_BITMAP *stopscene = NULL;

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *Medium_font = NULL;
    ALLEGRO_FONT *Large_font = NULL;

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *enemy_pro = NULL;

    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *clickSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *clearSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *failSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *backgroundSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *gameSound = NULL;


    LEVEL *level = NULL;
    Menu *menu = NULL;

    Character* jacket;
    std::vector<Character*> enemies;
    std::vector<Weapon*> weapons;

    int mouse_x, mouse_y;
    int board_x = 0, board_y = 0;
    int preGameState = 0, GameState = 0;

    bool update = false;
    bool mute = false;
    bool dir_keys[DirKeysUsed] = {false};
    bool game_keys[GameKeysUsed] = {false};
    bool func_keys[FuncKeysUsed] = {false};
    bool mouse_hold = false;
    bool PAUSE = false;
};


#endif // MAINWINDOW_H_INCLUDED
