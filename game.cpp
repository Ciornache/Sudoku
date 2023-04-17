#include "game.h"

Game::Game()
{
    table = new Table(TABLE_HEIGHT, TABLE_WIDTH);
}

void Game::initializeStyle()
{
    settextstyle(BOLD_FONT, 0, 5);
    setcolor(BLACK);
}

void Game::start()
{
    table->init();
    initializeStyle();
    run();
}

void Game::run()
{
    printSolution();
    while(1)
    {
        int xCoordinate = -1, yCoordinate = -1;

        getClick(xCoordinate, yCoordinate);
        Square * square = table->findSpecialSquare(xCoordinate, yCoordinate);
        if(square == NULL)
        {
            std::cout << "WRONG INPUT\n";
            continue;
        }

        while(1)
        {
            getClick(xCoordinate, yCoordinate);
            Square * targetSquare = table->findSquare(xCoordinate, yCoordinate);
            if(targetSquare == NULL)
            {
                std::cout << "WRONG INPUT\n";
                continue;
            }

            char value = targetSquare->getValue();
            if(value != ' ')
            {
                std::cout << "WRONG INPUT\n";
                continue;
            }

            break;
        }

        Square * targetSquare = table->findSquare(xCoordinate, yCoordinate);
        targetSquare->setValue(square->getValue());

        bool validMove = table->checkGrid();
        if(!validMove)
        {
            targetSquare->setValue('!');
            targetSquare->placeValue(BOLD_FONT, 0, RED);
            system("PAUSE");
            targetSquare->setValue(' ');
            targetSquare->placeValue(BOLD_FONT, 0, BLACK);
            continue;
        }
        targetSquare->placeValue(BOLD_FONT, 0, BLACK);

    }
}

void Game::getClick(int &x, int &y)
{
    while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, x, y);
}

void Game::printSolution()
{
    std::vector<cell> solution = table->solver->getSolution();

    std::random_shuffle(solution.begin(), solution.end());

    for(int i = 0;i < solution.size(); ++i)
    {

        int row = START_X + (solution[i].row - 1) * SQUARE_SIZE;
        int column = START_Y + (solution[i].column - 1) * SQUARE_SIZE;
        Square * square = table->findSquare(column, row);
//        std::cout << square->getStartX() << ' ' << square->getStartY() << '\n';
        square->setValue(solution[i].value + '0');
        square->placeValue(BOLD_FONT, 0, BRIGHT_RED);
        pause(1);
        square->placeValue(BOLD_FONT, 0, BLACK);
        pause(2);
    }
}

void Game::pause(int seconds)
{
    int realSeconds = seconds * SECONDS_BUFFER;
    while(realSeconds)
        realSeconds--;
}
