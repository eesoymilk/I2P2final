#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <allegro5/allegro_font.h>

#define MoveKeysUsed 5
enum {W_KEY=0, A_KEY, S_KEY, D_KEY, LSHIFT_KEY};
#define GameKeysUsed 3
enum {E_KEY = 0, R_KEY, G_KEY};
#define FuncKeysUsed 4
enum {ENTER_KEY=0, P_KEY, H_KEY, ESCAPE_KEY};
const int draw_frequency = 10;

#define font_size 50
#define grid_width 40
#define grid_height 40

#define window_width 1920
#define window_height 1080
#define field_width 800
#define field_height 600
#define CharacterScale 3

#define NumOfGrid (field_width / grid_width) * (field_height / grid_height)


extern int TowerRadius[];
extern char TowerClass[][20];
extern int TowerWidth[];
extern int TowerHeight[];
extern int background_width;
extern int background_height;
extern int Character_Health;

// the origin of camera
extern int camera_origin_x;
extern int camera_origin_y;

const int hud_width = 600;
const int hud_height = 200;
const int font_start = 20;

enum {ARCANE = 0, ARCHER, CANON, POISON, STORM};
enum {WOLF = 0, WOLFKNIGHT, DEMONNIJIA, CAVEMAN};

#endif // GLOBAL_H_INCLUDED
