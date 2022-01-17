#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <list>
#include <time.h>
#include "Bullet.h"
#include "Slider.h"

// EDITED
#include "Jacket.h"
#include "Enemy.h"
#include "Pistol.h"
#include "SubmachineGun.h"
#include "AssaultRifle.h"
#include "Wall.h"
//

#define GAME_EXIT -1
#define GAME_CONTINUE 0
// #define GAME_NEXT 1
// #define GAME_STOP 2

#define GAMESTATE_MENU      0
#define GAMESTATE_TUTORIAL  1
#define GAMESTATE_PLAYING   2
#define GAMESTATE_PAUSE     3
#define GAMESTATE_SUCCESS   4
#define GAMESTATE_FAILURE   5
#define GAMESTATE_END       6

#define MaxSpeed 3
#define Acceleration 1

// clock rate
const float FPS = 60;

// total number of level
const int LevelNum = 4;

class GameWindow
{
public:
    // constructor
    GameWindow();
    // each process of scene
    void game_reset();
    void game_play();
    void game_begin(int);
    void game_menu();
    void level_init(int);

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
    bool wallBetween(Wall* wall, int x1, int y1, int x2, int y2);

    // Tower* create_tower(int);
    // Monster* create_monster();
    Jacket* spawnJacket(int, int);
    Enemy* spawnEnemy(int, int, int);
    Weapon* spawnWeapon(int, int, int);

public:
    bool initial = true;

private:
    ALLEGRO_BITMAP *icon;
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_BITMAP *startscene = NULL;
    ALLEGRO_BITMAP *helpscene = NULL;
    ALLEGRO_BITMAP *stopscene = NULL;
    ALLEGRO_BITMAP *clearscene = NULL;
    ALLEGRO_BITMAP *failscene = NULL;

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *Medium_font = NULL;
    ALLEGRO_FONT *Large_font = NULL;
    ALLEGRO_FONT *hudFont = NULL;

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *enemy_pro = NULL;
    ALLEGRO_TIMER *record_time = NULL;

    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *clickSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *clearSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *failSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *backgroundSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *gameSound = NULL;

    Jacket* jacket;
    std::vector<std::pair<int, int>> LevelMap;
    std::vector<Enemy*> enemies;
    std::vector<Weapon*> weapons;
    std::vector<Wall*> WallMap;

    int mouse_x, mouse_y;
    int board_x = 0, board_y = 0;
    int preGameState = 0, GameState = 0, level = 0;
    int Node_Amount = 0;
    int Wall_Amount = 0;
    int Door_Amount = 0;
    long long int record[3];

    bool update = false;
    bool mute = false;
    bool move_keys[MoveKeysUsed] = {false};
    bool game_keys[GameKeysUsed] = {false};
    bool func_keys[FuncKeysUsed] = {false};
    bool mouse_hold = false;
};


#endif // MAINWINDOW_H_INCLUDED
