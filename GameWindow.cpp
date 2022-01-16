#include "GameWindow.h"
#include "global.h"
#include <iostream>
#include <algorithm>

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)
#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))


// EDITED

#define MaxLevel 4
#define Acceleration 5
const int draw_frequency = 10;
int background_width;
int background_height;
int Character_Health;
int camera_origin_x;
int camera_origin_y;

void
GameWindow::game_init()
{
    level = new LEVEL(1);
    menu = new Menu();
}

bool
GameWindow::mouse_hover(int startx, int starty, int width, int height)
{
    if(mouse_x >= startx && mouse_x <= startx + width)
        if(mouse_y >= starty && mouse_y <= starty + height)
            return true;

    return false;
}

Character*
GameWindow::spawnCharacter(int type, int x, int y)
{
    Character* c = NULL;
    switch (type)
    {
    case 1:
        c = new Jacket(x, y);
        break;
    default:
        break;
    }
    return c;
}

Weapon*
GameWindow::spawnWeapon(int type, int x, int y)
{
    int i = SMG;
    Weapon* w = NULL;
    switch (type)
    {
    case 1:
        w = new Pistol();
        printf("Dropping Pistol...\n");
        w->Drop(x, y);
        break;
    case 2:
        w = new SubmachineGun();
        printf("Dropping SMG...\n");
        w->Drop(x, y);
        break;
    case 3:
        w = new AssaultRifle();
        printf("Dropping AR...\n");
        w->Drop(x, y);
        break;
    default:
        break;
    }
    return w;
}

void
GameWindow::game_play()
{
    int msg = GAME_CONTINUE;
    printf("Using srand() for no reasons...\n");
    srand(time(NULL));
    printf("Init Menu...\n");
    game_menu();
    while (msg != GAME_EXIT)
    {
        msg = game_run();
    }
    show_err_msg(msg);
    game_destroy();
}

void
GameWindow::show_err_msg(int msg)
{
    if(msg == GAME_EXIT)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);

    game_destroy();
    exit(9);
}

GameWindow::GameWindow()
{
    if (!al_init())
        show_err_msg(-1);

    printf("Game Initializing...\n");

    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();

    timer = al_create_timer(1.0 / FPS);
    enemy_pro = al_create_timer(1.0 / FPS);

    if(timer == NULL || enemy_pro == NULL)
        show_err_msg(-1);

    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);

    printf("Allegro Init...\n");
    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon
    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    printf("Loading Founts...\n");
    font = al_load_ttf_font("Caviar_Dreams_Bold.ttf", 12,0);        // load small font
    Medium_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf", 24,0); // load medium font
    Large_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf", 36,0);  // load large font

    printf("Registering Events...\n");
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(enemy_pro));


    board_x = 0; board_y = 0;

    char buffer[50];

    printf("Loading Bitmaps...\n");
    icon = al_load_bitmap("./icon.jpg");
    background = al_load_bitmap("./Map1.png");
    startscene = al_load_bitmap("./Scene.jpg");
    helpscene = al_load_bitmap("./HelpScene.jpg");
    stopscene = al_load_bitmap("./StopScene.png");
    background_width = al_get_bitmap_width(background);
    background_height = al_get_bitmap_height(background);

    al_set_display_icon(display, icon);
    al_reserve_samples(3);

    printf("Loading Sounds...\n");
    sample = al_load_sample("ClickSound.ogg");
    clickSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(clickSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(clickSound, al_get_default_mixer());

    sample = al_load_sample("BackgroundMusic.ogg");
    backgroundSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());

    sample = al_load_sample("Paris.ogg");
    gameSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(gameSound, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(gameSound, al_get_default_mixer());

    printf("Starting Timer...\n");
    al_start_timer(timer);
}

void
GameWindow::game_menu()
{
    game_reset();
    printf(">>> Menu...\n");
    al_play_sample_instance(backgroundSound);
    Draw();
}

void
GameWindow::game_begin()
{
    game_reset();
    printf(">>> In Game <<<\n");

    if (jacket) delete jacket;
    weapons.clear();

    // tmp init for debugging
    jacket = spawnCharacter(1, 0, 0);
    printf("Spawning Weapon...\n");
    weapons.push_back(spawnWeapon(1, 200, 200));
    weapons.push_back(spawnWeapon(2, 200, 300));
    weapons.push_back(spawnWeapon(3, 200, 400));
    //

    Draw();

    /*al_play_sample_instance(startSound);
    while(al_get_sample_instance_playing(startSound));*/
    al_play_sample_instance(gameSound);
    al_start_timer(enemy_pro);
}

int
GameWindow::game_run()
{
    // printf("Game Running...\n");
    int message = GAME_CONTINUE;

    if (!al_is_event_queue_empty(event_queue))
        message = process_event();
    
    if (message == GAME_NEXT) {
        switch (GameState)
        {
        case GAMESTATE_MENU:        GameState = GAMESTATE_INGAME;   break;
        case GAMESTATE_INGAME:      GameState = GAMESTATE_END;      break;
        case GAMESTATE_TUTORIAL:    GameState = GAMESTATE_MENU;     break;
        case GAMESTATE_PAUSE:       GameState = GAMESTATE_INGAME;   break;
        case GAMESTATE_END:         GameState = GAMESTATE_MENU;
        }
    } else if (message == GAME_STOP) {
        switch (GameState)
        {
        case GAMESTATE_MENU:        GameState = GAMESTATE_TUTORIAL; break;
        case GAMESTATE_INGAME:      GameState = GAMESTATE_PAUSE;    break;
        case GAMESTATE_TUTORIAL:    GameState = GAMESTATE_MENU;     break;
        case GAMESTATE_PAUSE:       GameState = GAMESTATE_MENU;     break;
        }
    }

    return message;
}

int
GameWindow::game_update()
{
    int message = GAME_CONTINUE;
    if (func_keys[ENTER_KEY]) {
        func_keys[ENTER_KEY] = false;
        if (GameState != GAMESTATE_INGAME)
            message = GAME_NEXT;
    } else if (func_keys[H_KEY]) {
        func_keys[H_KEY] = false;
        if (GameState == GAMESTATE_TUTORIAL)
            message = GAME_NEXT;
        else if (GameState == GAMESTATE_MENU)
            message = GAME_STOP;
    } else if (func_keys[ESCAPE_KEY]) {
        func_keys[ESCAPE_KEY] = false;
        if (GameState == GAMESTATE_MENU || GameState == GAMESTATE_END)
            message = GAME_EXIT;
        else
            message = GAME_STOP;
    }

    if (GameState == GAMESTATE_MENU && (preGameState == GAMESTATE_PAUSE || preGameState == GAMESTATE_END)) {
        game_menu();
    }

    if (GameState == GAMESTATE_INGAME) {
        if (preGameState == GAMESTATE_MENU) {
            printf("Game Begins!!!\n");
            game_begin();
        }
        Weapon* w = jacket->getWeapon();
        
        if (game_keys[E_KEY]) {
            game_keys[E_KEY] = false;
            std::vector<Weapon*> near_weapons;
            Weapon* pick_target;
            Circle* jacket_cirle = jacket->getCircle();

            for (auto weapon : weapons) {
                if (weapon->isDropped() && Circle::isOverlap(jacket_cirle, weapon->getCircle()))
                    near_weapons.push_back(weapon);
            }

            if (!near_weapons.empty()) {
                printf("Picking Weapon...\n");
                pick_target = *near_weapons.begin();
                double min_distance = Circle::Distance(jacket_cirle, pick_target->getCircle());
                for (int i = 1; i < near_weapons.size(); i++) {
                    double distance = Circle::Distance(jacket_cirle, pick_target->getCircle());
                    if (distance < min_distance) {
                        min_distance = distance;
                        pick_target = near_weapons[i];
                    }
                }
                jacket->PickWeapon(pick_target);
            }
        }

        if (game_keys[R_KEY]) {
            game_keys[R_KEY] = false;
            if (w)  w->StartReload();
        }

        if (game_keys[G_KEY]) {
            game_keys[G_KEY] = false;
            if (w)  w->Drop(jacket->getX(), jacket->getY());
        }

        if (w) {
            if (w->isReloading()) {
                w->Reload();
            } else {
                w->CoolDown();
                if (mouse_hold) jacket->FireWeapon(mouse_x, mouse_y);
            }
        }
        
        jacket->Move(dir_keys);
        for (auto bullet : jacket->getBullets())    bullet->Move();

        camera_origin_x = jacket->getCircle()->x - window_width / 2;
        camera_origin_y = jacket->getCircle()->y - window_height / 2;
        if(camera_origin_x < 0) camera_origin_x = 0;
        if(camera_origin_x > background_width - window_width) camera_origin_x = background_width - window_width;
        if(camera_origin_y > background_height - window_height) camera_origin_y = background_height - window_height;
        if(camera_origin_y < 0) camera_origin_y = 0;
        board_x = camera_origin_x;
        board_y = camera_origin_y;
    
    }

    preGameState = GameState;

    return message;
}

void
GameWindow::game_reset()
{   
    printf("Resetting...\n");
    mute = false;
    update = false;

    printf("Stop All Sounds...\n");
    // stop sample instance
    al_stop_sample_instance(backgroundSound);
    al_stop_sample_instance(gameSound);
    al_stop_sample_instance(clickSound);

    printf("Stop All Timers...\n");
    // stop timer
    // al_stop_timer(timer);
    al_stop_timer(enemy_pro);
}

void
GameWindow::game_destroy()
{
    game_reset();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);

    al_destroy_timer(timer);
    al_destroy_timer(enemy_pro);

    al_destroy_bitmap(icon);
    al_destroy_bitmap(background);
    al_destroy_bitmap(helpscene);
    al_destroy_bitmap(startscene);

    al_destroy_sample(sample);
    al_destroy_sample_instance(clickSound);
    al_destroy_sample_instance(gameSound);
    al_destroy_sample_instance(backgroundSound);

    delete level;
    delete menu;
}

int
GameWindow::process_event()
{
    int message = GAME_CONTINUE;

    al_wait_for_event(event_queue, &event);
    // printf("Event Processing...\n");

    update = false;

    if (event.type == ALLEGRO_EVENT_TIMER) {
        // printf(">>> Timer Event\n");
        if (event.timer.source == timer) {
            update = true;
        }
    }
    else {
        // printf(">>> Not Timer Event\n");
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            // printf(">>> Display Closed\n");
            return GAME_EXIT;
        } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
                // GAMEPLAY KEYS
                case ALLEGRO_KEY_W:
                    printf("W is pressed!\n");
                    if (!dir_keys[W_KEY]) dir_keys[W_KEY] = true;
                    break;
                case ALLEGRO_KEY_A:
                    printf("A is pressed!\n");
                    if (!dir_keys[A_KEY]) dir_keys[A_KEY] = true;
                    break;
                case ALLEGRO_KEY_S:
                    printf("S is pressed!\n");
                    if (!dir_keys[S_KEY]) dir_keys[S_KEY] = true;
                    break;
                case ALLEGRO_KEY_D:
                    printf("D is pressed!\n");
                    if (!dir_keys[D_KEY]) dir_keys[D_KEY] = true;
                    break;
                case ALLEGRO_KEY_E:
                    printf("E is pressed!\n");
                    game_keys[E_KEY] = true;
                    break;
                case ALLEGRO_KEY_R:
                    printf("R is pressed!\n");
                    game_keys[R_KEY] = true;
                    break;
                case ALLEGRO_KEY_G:
                    printf("E is pressed!\n");
                    game_keys[G_KEY] = true;
                    break;

                // FUNCTION KEYS
                case ALLEGRO_KEY_ENTER:
                    func_keys[ENTER_KEY] = true;
                    break;
                case ALLEGRO_KEY_P:
                    func_keys[P_KEY] = true;
                    break;
                case ALLEGRO_KEY_H:
                    func_keys[H_KEY] = true;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    func_keys[ESCAPE_KEY] = true;
                    break;
            }
        } else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_W:
                    printf("W is released!\n");
                    if (dir_keys[W_KEY])    dir_keys[W_KEY] = false;
                    break;
                case ALLEGRO_KEY_A:
                    printf("A is released!\n");
                    if (dir_keys[A_KEY])    dir_keys[A_KEY] = false;
                    break;
                case ALLEGRO_KEY_S:
                    printf("S is released!\n");
                    if (dir_keys[S_KEY])    dir_keys[S_KEY] = false;
                    break;
                case ALLEGRO_KEY_D:
                    printf("D is released!\n");
                    if (dir_keys[D_KEY])    dir_keys[D_KEY] = false;
                    break;
            }
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if(event.mouse.button == 1) {
                if (!mouse_hold)    mouse_hold = true;
            }
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            if (event.mouse.button == 1) {
                if (mouse_hold)     mouse_hold = false;
            }
        } else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            if (GameState == GAMESTATE_INGAME) {
                mouse_x = event.mouse.x;
                mouse_y = event.mouse.y;
                // printf("mouse_x = %d, mouse_y = %d\n", mouse_x, mouse_y);
                jacket->setRadianCCW(mouse_x, mouse_y);
                //menu->MouseIn(mouse_x, mouse_y);
            }
        }

    }

    // printf("Event Processed.\n");

    if(update) {
        // update each object in game
        message = game_update();

        // Re-draw map
        Draw();
        update = false;
    }

    return message;
}

void
GameWindow::Draw()
{
    if (GameState == GAMESTATE_MENU) {
        // printf("Drawing Menu...\n");
        al_draw_bitmap(startscene, 0, 0, 0);
    } else if (GameState == GAMESTATE_INGAME) {
        printf("Drawing Gamescene...\n");
        printf("Drawing Map...\n");
        al_draw_bitmap(background, -board_x, -board_y, 0);
        printf("Drawing Weapon...\n");
        for (auto weapon : weapons) weapon->Draw();
        printf("Drawing Jacket...\n");
        jacket->Draw();
        // menu->Draw();
    } else if (GameState == GAMESTATE_TUTORIAL) {
        al_draw_bitmap(helpscene, 0, 0, 0);
    } else if (GameState == GAMESTATE_PAUSE) {
        al_draw_bitmap(stopscene, 0, 0, 0);
    } else if (GameState == GAMESTATE_END) {
        // TODO
    }
    al_flip_display();
}
