#include "GameWindow.h"
#include "global.h"
#include <iostream>

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
    char buffer[50];

    icon = al_load_bitmap("./icon.jpg");
    background = al_load_bitmap("./Map1.png");
    startscene = al_load_bitmap("./Scene.jpg");
    helpscene = al_load_bitmap("./HelpScene.jpg");
    stopscene = al_load_bitmap("./StopScene.png");
    background_width = al_get_bitmap_width(background);
    background_height = al_get_bitmap_height(background);

    al_set_display_icon(display, icon);
    al_reserve_samples(3);

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

// Tower*
// GameWindow::create_tower(int type)
// {
//     Tower *t = NULL;
//     if(isOnRoad())
//         return t;
//     switch(type)
//     {
//     case ARCANE:
//         t = new Arcane(mouse_x, mouse_y);
//         break;
//     case ARCHER:
//         t = new Archer(mouse_x, mouse_y);
//         break;
//     case CANON:
//         t = new Canon(mouse_x, mouse_y);
//         break;
//     case POISON:
//         t = new Poison(mouse_x, mouse_y);
//         break;
//     case STORM:
//         t = new Storm(mouse_x, mouse_y);
//         break;
//     default:
//         break;
//     }
//     menu->Change_Coin(menu->getTowerCoin(type));
//     return t;
// }

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
    Weapon* w = NULL;
    switch (type)
    {
    case 1:
        w = new Pistol();
        printf("Dropping Pistol...\n");
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
    int msg;

    srand(time(NULL));

    msg = -1;
    game_reset();
    game_begin();

    while(msg != GAME_EXIT)
    {
        msg = game_run();
    }

    show_err_msg(msg);
}

void
GameWindow::show_err_msg(int msg)
{
    if(msg == GAME_TERMINATE)
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

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",12,0); // load small font
    Medium_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",24,0); //load medium font
    Large_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",36,0); //load large font

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(enemy_pro));

    board_x = 0; board_y = 0;

    game_init();
}

void
GameWindow::game_begin()
{
    printf(">>> Start Level[%d]\n", level->getLevel());

    al_play_sample_instance(backgroundSound);
    draw_startscene();

    al_stop_sample_instance(backgroundSound);

    // tmp init for debugging
    jacket = spawnCharacter(1, 0, 0);
    printf("Spawning pistol...\n");
    weapons.push_back(spawnWeapon(1, 4, 4));
    printf("Spawned pistol.\n");
    //

    draw_running_map();

    /*al_play_sample_instance(startSound);
    while(al_get_sample_instance_playing(startSound));*/
    al_play_sample_instance(gameSound);

    al_start_timer(timer);
    al_start_timer(enemy_pro);
}

int
GameWindow::game_run()
{
    int error = GAME_CONTINUE;

    if (!al_is_event_queue_empty(event_queue)) {
        error = process_event();
    }
    return error;
}

int
GameWindow::game_update()
{
    unsigned int i, j;

    if (function_key_pressed) {
        function_key_pressed = false;
        std::vector<Weapon*> near_weapons;
        Weapon* pick_target;
        Circle* jacket_cirle = jacket->getCircle();
        
        for (auto weapon : weapons) {
            if (weapon->isDropped() && Circle::isOverlap(jacket_cirle, weapon->getCircle()))
                near_weapons.push_back(weapon);
        }

        if (!near_weapons.empty()) {
            printf("Picking Weapon...\n");
            if (near_weapons.size() == 1)   pick_target = *near_weapons.begin();
            jacket->PickWeapon(pick_target);
            pick_target->Pick();
        }
    }

    jacket->Move(hold);
    for (auto bullet : jacket->getBullets())
        bullet->Move();

    Weapon* w = jacket->getWeapon();
    if (w != NULL)  w->CoolDown();

    if (mouse_hold) {
        if (jacket->getWeapon())
            jacket->DoAttack(mouse_x, mouse_y);
    }
    camera_origin_x = jacket->getCircle()->x - window_width / 2;
    camera_origin_y = jacket->getCircle()->y - window_height / 2;
    //printf("Board1: %d %d\n", board_x, board_y);
    if(camera_origin_x < 0) camera_origin_x = 0;
    if(camera_origin_x > background_width - window_width) camera_origin_x = background_width - window_width;
    if(camera_origin_y > background_height - window_height) camera_origin_y = background_height - window_height;
    if(camera_origin_y < 0) camera_origin_y = 0;

    board_x = camera_origin_x;
    board_y = camera_origin_y;
    //printf("Board2: %d %d\n", board_x, board_y);

    //WindowMove();

    // /*TODO:*/
    // /*Allow towers to detect if monster enters its range*/
    // /*Hint: Tower::DetectAttack*/
    // for(auto _tower: towerSet){
    //     for(auto _monster: monsterSet){
    //         if(_tower->DetectAttack(_monster)) break;
    //     }
    // }
    // // update every monster
    // // check if it is destroyed or reaches end point
    // for(i=0; i < monsterSet.size(); i++)
    // {
    //     bool isDestroyed = false, isReachEnd = false;
    // /*TODO:*/
    // /*1. For each tower, traverse its attack set*/
    // /*2. If the monster collide with any attack, reduce the HP of the monster*/
    // /*3. Remember to set isDestroyed to "true" if monster is killed*/
    // /*Hint: Tower::TriggerAttack*/
    // for(auto _tower: towerSet)
    //     isDestroyed = _tower->TriggerAttack(monsterSet[i]);
    //     isReachEnd = monsterSet[i]->Move();
    //     if(isDestroyed)
    //     {
    //         Monster *m = monsterSet[i];
    //         menu->Change_Coin(m->getWorth());
    //         menu->Gain_Score(m->getScore());
    //         monsterSet.erase(monsterSet.begin() + i);
    //         i--;
    //         delete m;
    //     }
    //     else if(isReachEnd)
    //     {
    //         Monster *m = monsterSet[i];
    //         if(menu->Subtract_HP())
    //             return GAME_EXIT;
    //         monsterSet.erase(monsterSet.begin() + i);
    //         i--;
    //         delete m;
    //     }
    // }
    // /*TODO:*/
    // /*1. Update the attack set of each tower*/
    // /*Hint: Tower::UpdateAttack*/
    // for(auto _tower: towerSet)
    //     _tower->UpdateAttack();
    // return GAME_CONTINUE;
}

void
GameWindow::game_reset()
{
    mute = false;
    redraw = false;
    menu->Reset();

    // stop sample instance
    al_stop_sample_instance(backgroundSound);
    al_stop_sample_instance(gameSound);
    al_stop_sample_instance(clickSound);

    // stop timer
    al_stop_timer(timer);
    al_stop_timer(enemy_pro);
    // al_stop_timer(monster_pro);
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
    int i;
    int instruction = GAME_CONTINUE;

    // offset for pause window
    int offsetX = field_width/2 - 200;
    int offsetY = field_height/2 - 200;

    al_wait_for_event(event_queue, &event);
    redraw = false;

    int pause = 0;
    if(event.type == ALLEGRO_EVENT_TIMER) {
        if(event.timer.source == timer) {
            redraw = true;
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_W:
                printf("W is pressed!\n");
                if (!hold[W_KEY] && !PAUSE)    hold[W_KEY] = true;
                break;
            case ALLEGRO_KEY_A:
                printf("A is pressed!\n");
                if (!hold[A_KEY] && !PAUSE)    hold[A_KEY] = true;
                break;
            case ALLEGRO_KEY_S:
                printf("S is pressed!\n");
                if (!hold[S_KEY] && !PAUSE)    hold[S_KEY] = true;
                break;
            case ALLEGRO_KEY_D:
                printf("D is pressed!\n");
                if (!hold[D_KEY] && !PAUSE)    hold[D_KEY] = true;
                break;
            case ALLEGRO_KEY_E:
                printf("E is pressed!\n");
                function_key_pressed = true;
                break;
            case ALLEGRO_KEY_P:
                if(!PAUSE){
                    al_stop_timer(timer);
                    al_stop_timer(enemy_pro);
                    PAUSE = true;
                }
                else{
                    al_start_timer(timer);
                    al_start_timer(enemy_pro);
                    PAUSE = false;
                }
                break;
            case ALLEGRO_KEY_R:
                if(PAUSE){
                    PAUSE = false;
                    game_play();
                }
                break;
            case ALLEGRO_KEY_ESCAPE:
                if(PAUSE){
                    PAUSE = false;
                    game_play();
                }
                break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP) {
        switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_W:
                printf("W is released!\n");
                if (hold[W_KEY] && !PAUSE)    hold[W_KEY] = false;
                break;
            case ALLEGRO_KEY_A:
                printf("A is released!\n");
                if (hold[A_KEY] && !PAUSE)    hold[A_KEY] = false;
                break;
            case ALLEGRO_KEY_S:
                printf("S is released!\n");
                if (hold[S_KEY] && !PAUSE)    hold[S_KEY] = false;
                break;
            case ALLEGRO_KEY_D:
                printf("D is released!\n");
                if (hold[D_KEY] && !PAUSE)    hold[D_KEY] = false;
                break;
        }
    }
    else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if(event.mouse.button == 1) {
            if (!mouse_hold)    mouse_hold = true;
        }
    } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
        if (event.mouse.button == 1) {
            if (mouse_hold)     mouse_hold = false;
        }
    } else if (event.type == ALLEGRO_EVENT_MOUSE_AXES){
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
        // printf("mouse_x = %d, mouse_y = %d\n", mouse_x, mouse_y);
        jacket->setRadianCCW(mouse_x, mouse_y);
        //menu->MouseIn(mouse_x, mouse_y);
    }

    if(PAUSE){
        al_draw_bitmap(stopscene, 0, 0, 0);
        al_flip_display();
    }

    if(redraw) {
        // update each object in game
        instruction = game_update();

        // Re-draw map
        draw_running_map();
        redraw = false;
    }

    return instruction;
}

void
GameWindow::draw_running_map()
{
    //unsigned int i, j;

    al_clear_to_color(al_map_rgb(0, 0, 0));

    //al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_bitmap(background, -board_x, -board_y, 0);
    for (auto weapon : weapons) weapon->Draw();
    jacket->Draw();

    //printf("%d %d\n", x_axis, y_axis);
    //al_draw_bitmap_region(background, 0, 0, 1200, 800, 0, 0, 0);
    //al_draw_bitmap_region(background, 60, 400, 1200, 800, jacket->getCircle()->x - 400, jacket->getCircle()->y - 400, 0);
    //al_draw_bitmap(background, jacket->getCircle()->x - 400, jacket->getCircle()->y - 300, 0);

    /*for(i = 0; i < field_height/40; i++)
    {
        for(j = 0; j < field_width/40; j++)
        {
            char buffer[50];
            sprintf(buffer, "%d", i*15 + j);
            if(level->isRoad(i*15 + j)) {
                al_draw_filled_rectangle(j*40, i*40, j*40+40, i*40+40, al_map_rgb(255, 244, 173));
            }
            //al_draw_text(font, al_map_rgb(0, 0, 0), j*40, i*40, ALLEGRO_ALIGN_CENTER, buffer);
        }
    }
    for(i=0; i<monsterSet.size(); i++)
    {
        monsterSet[i]->Draw();
    }*/

    /*for(std::list<Tower*>::iterator it = towerSet.begin(); it != towerSet.end(); it++)
        (*it)->Draw();

    if(selectedTower != -1)
        Tower::SelectedTower(mouse_x, mouse_y, selectedTower);

    al_draw_filled_rectangle(field_width, 0, window_width, window_height, al_map_rgb(100, 100, 100));

    menu->Draw();*/

    al_flip_display();
}

// void GameWindow::SetVx(int v) {
//     if (v > MaxSpeed)       vx = MaxSpeed;
//     else if (v < -MaxSpeed) vx = -MaxSpeed;
//     else                    vx = v;
// }

// void GameWindow::SetVy(int v){
//     if (v > MaxSpeed)       vy = MaxSpeed;
//     else if (v < -MaxSpeed) vy = -MaxSpeed;
//     else                    vy = v;
// }

void
GameWindow::draw_startscene()
{
    bool start_button = false;
    bool help_button = false;

    //al_clear_to_color(al_map_rgb(100, 100, 100));
    //al_draw_bitmap_region(background, jacket->getCircle()->x - 20, jacket->getCircle()->y - 20, 1200, 800, 0, 0, 0);
    //al_draw_bitmap_region(background, 60, 400, 1200, 800, jacket->getCircle()->x - 400, jacket->getCircle()->y - 400, 0);
    while(!start_button){
        if (!al_is_event_queue_empty(event_queue)) {
            al_wait_for_event(event_queue, &event);
            if(event.type == ALLEGRO_EVENT_KEY_DOWN){
                switch(event.keyboard.keycode){
                    case ALLEGRO_KEY_S:
                        al_play_sample_instance(clickSound);
                        while(al_get_sample_instance_playing(clickSound));
                        start_button = true;
                        break;
                    case ALLEGRO_KEY_T:
                        al_play_sample_instance(clickSound);
                        if(help_button) help_button = false;
                        else help_button = true;
                        break;
                    case ALLEGRO_KEY_E:
                        game_destroy();
                        break;
                }
            }
        }
        //if(help_button) printf("1\n");
        //else printf("0\n");
        if(help_button) al_draw_bitmap(helpscene, 0, 0, 0);
        else al_draw_bitmap(startscene, 0, 0, 0);
        al_flip_display();
    }
}
