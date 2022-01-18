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

#define window_width 1920
#define window_height 1080
#define field_width 800
#define field_height 600
#define CharacterScale 4
#define WeaponScale 1.5
#define CharacterWidth 36

extern int background_width;
extern int background_height;
extern int Character_Health;

// the origin of camera
extern int camera_origin_x;
extern int camera_origin_y;

const int hud_width = 600;
const int hud_height = 200;
const int font_start = 20;

#endif // GLOBAL_H_INCLUDED
