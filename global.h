#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <allegro5/allegro_font.h>

#define DirKeysUsed 4
enum {W_KEY=0, A_KEY, S_KEY, D_KEY};
#define GameKeysUsed 3
enum {E_KEY = 0, R_KEY, G_KEY};
#define FuncKeysUsed 4
enum {ENTER_KEY=0, P_KEY, H_KEY, ESCAPE_KEY};

#define font_size 30
#define grid_width 40
#define grid_height 40

#define window_width 1920
#define window_height 1080
#define field_width 800
#define field_height 600

#define Num_TowerType 5
#define Num_MonsterType 4
#define NumOfGrid (field_width / grid_width) * (field_height / grid_height)

#define CharacterScale 3

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

enum {ARCANE = 0, ARCHER, CANON, POISON, STORM};
enum {WOLF = 0, WOLFKNIGHT, DEMONNIJIA, CAVEMAN};

#endif // GLOBAL_H_INCLUDED
