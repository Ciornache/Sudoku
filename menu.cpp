#include "menu.h"


Menu::Menu()
{
    type = squareColor = upperSquareColor = textColor = difficulty = -1;
}

void Menu::askForData()
{
    std::string command;
    while(1)
    {
        std::cout << "-> ";

        getline(cin, command);
        lowerCase(command);

        pair<std::string, int> instruction = extractCommand(command);

        if(instruction.first == "set type")
        {
            type = instruction.second;
            if(type < 1 || type > 2)
            {
                std::cout << "-> WRONG INPUT. CONSULT THE INSTRUCTIONS WITH THE COMMAND show instructions\n\n";
                continue;
            }
        }
        else if(instruction.first == "set difficulty")
        {
            difficulty = instruction.second;
            if(instruction.second < 1 || instruction.second > 5)
            {
                std::cout << "-> WRONG INPUT. CONSULT THE INSTRUCTIONS WITH THE COMMAND show instructions\n\n";
                continue;
            }
        }
        else if(instruction.first == "set square color")
            squareColor = instruction.second;
        else if(instruction.first == "set text color")
            textColor = instruction.second;
        else if(instruction.first == "set upper square color")
            upperSquareColor = instruction.second;
        else if(instruction.first == "show instructions")
        {
            std::cout << "-> The type of the game can only range from 1 to 2. 1 means you can play it yourself, 2 is just a simulation of the game. The default type is 1.\n";
            std::cout << "-> The difficulty can only range from 1 to 5, 1 being the hardest difficulty and 5 the lowest. The default difficulty is 3\n\n";
            std::cout << "-> The codes for the colors are this and only this. The default color is BLACK\n\n";
            std::cout << " -> BLACK : 0\n -> BLUE : 1\n -> GREEN : 2\n -> CYAN : 3\n -> RED : 4\n -> MANGENTA : 5\n -> BROWN : 6\n -> LIGHTGRAY : 7\n -> DARKGRAY : 8\n";
            std::cout << " -> LIGHTBLUE : 9\n -> LIGHTGREEEN : 10\n -> LIGHTCYAN : 11\n -> LIGHTRED : 12\n -> LIGHTMAGENTA : 13\n -> YELLOW : 14\n -> WHITE : 15\n\n";
        }
        else if(instruction.first == "ready")
            break;
        else
            std::cout << "-> WRONG INPUT. CONSULT THE INSTRUCTIONS WITH THE COMMAND show instructions\n\n";

    }
}

void Menu::lowerCase(string &text)
{
    for(int i = 0; i < text.size(); ++i)
    {
        if(text[i] >= 'A' && text[i] <= 'Z')
            text[i] = text[i] - 'A' + 'a';
    }
}

std::pair<std::string, int> Menu::extractCommand(string text)
{
    int j = text.size() - 1;
    while(j >= 0 && text[j] >= '0' && text[j] <= '9')
        j--;

    string command = text.substr(0, j + 1);

    while(command.size() > 0 && command.back() == ' ')
        command.pop_back();

    int number = -1;
    for(int i = j + 1; i < text.size(); ++i)
    {
        number = max(number, 0);
        number = number * 10 + text[i] - '0';
    }

    return {command, number};
}
