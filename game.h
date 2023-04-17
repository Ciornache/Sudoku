#ifndef H_GAME
#define H_GAME


#include "table.h"
#include "menu.h"

class Game
{
public:
     Game();
     void start();
     void ask();

private:

    Table * table;
    Menu * menu;

    void initializeStyle();
    void run();
    void getClick(int &x, int &y);
    void printSolution();
};



#endif // H_GAME
