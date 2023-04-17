#include "game.h"

using namespace std;

int main()
{
    Game * game = new Game;
    game->ask();
    game->start();
    getch();
}
