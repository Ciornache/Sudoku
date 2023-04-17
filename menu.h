#ifndef H_MENU
#define H_MENU

#include "config.h"

class Menu
{
public:
    Menu();
    void askForData();

private:

    std::pair<std::string, int> extractCommand(std::string text);
    void lowerCase(std::string & text);

};





#endif // H_MENU
