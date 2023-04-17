#include "game.h"

using namespace std;

int main()
{
    initwindow(700, 700, "Sudoku", 400, 150);
    Game * game = new Game;
    game->start();
    getch();
}
