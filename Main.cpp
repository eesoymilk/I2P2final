#include "GameWindow.h"

int main(int argc, char *argv[])
{
    GameWindow *TowerGame= new GameWindow();

    //TowerGame->draw_startscene();

    TowerGame->game_play();

    delete TowerGame;
    return 0;
}
