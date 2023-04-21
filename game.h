#ifndef H_GAME
#define H_GAME


#include "table.h"
#include "menu.h"

class Game
{
public:

    ~Game();
     Game();
     void start();
     void ask();

private:

    int healthPoints = 3;
    int numberOfHints = 3;
    int goodMoves = 0;

    Table * table;
    Menu * menu;

    Square * pickRandomCell();

    void initializeLightBulb(char path[]);
    void initializeHealthPoints(char path[]);
    void initializeStyle();

    void run();
    void getClick(int &x, int &y);
    void printSolution();

    void finish(char path[]);
    void giveHint();
};



#endif // H_GAME
