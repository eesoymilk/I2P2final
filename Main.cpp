#include "GameWindow.h"

int main(int argc, char *argv[])
{
    GameWindow *CyperPunk2069= new GameWindow();

    CyperPunk2069->game_play();

    delete CyperPunk2069;
    return 0;
}
