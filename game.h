#ifndef H_GAME
#define H_GAME


#include "table.h"


class Game
{
public:
     Game();
     void start();

private:

    Table * table;
    void initializeStyle();
    void run();
    void getClick(int &x, int &y);
    void printSolution();
    void pause(int seconds);
};



#endif // H_GAME
