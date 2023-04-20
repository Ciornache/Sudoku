#include "game.h"


Game::Game()
{
    table = new Table(TABLE_HEIGHT, TABLE_WIDTH);
    menu = new Menu;
    initwindow(700, 700, "Sudoku", 400, 50);
    healthPoints = 3;
}

Game::~Game()
{
    delete table;
    delete menu;
}

void Game::initializeStyle()
{
    settextstyle(BOLD_FONT, 0, 5);
    setcolor(BLACK);
    initializeHealthPoints("props/heart.jpg");
    initializeLightBulb("props/lightbulb.jpg");
}

void Game::start()
{
    if(type == -1)
        type = 1;

    table->init();
    initializeStyle();
    run();
}

void Game::run()
{
    if(type == 2)
    {
        printSolution();
        return;
    }

    while(1)
    {
        if(table->isEmpty())
        {
            std::cout << "-> YOU WON!";
            finish("props/likeEmoji.jpg");
        }

        int xCoordinate = -1, yCoordinate = -1;

        getClick(xCoordinate, yCoordinate);

        bool isLightBulb = table->checkLightBulb(xCoordinate, yCoordinate);
        if(isLightBulb && numberOfHints > 0)
        {
            numberOfHints--;
            giveHint();
            continue;
        }

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
            table->removeHeart(healthPoints);
            healthPoints--;

            if(healthPoints == 0)
            {
                std::cout << "-> YOU LOST!";
                finish("props/dislikeEmoji.jpg");
            }

            targetSquare->setValue('!');
            targetSquare->placeValue(BOLD_FONT, 0, BRIGHT_RED, 0);

            pause(2);

            targetSquare->setValue(' ');
            targetSquare->placeValue(BOLD_FONT, 0, textColor, 0);
            continue;
        }
        targetSquare->placeValue(BOLD_FONT, 0, textColor, 0);
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

    for(int i = 0; i < solution.size(); ++i)
    {

        int row = START_X + (solution[i].row - 1) * SQUARE_SIZE;
        int column = START_Y + (solution[i].column - 1) * SQUARE_SIZE;
        Square * square = table->findSquare(column, row);
//        std::cout << square->getStartX() << ' ' << square->getStartY() << '\n';
        square->setValue(solution[i].value + '0');
        square->placeValue(BOLD_FONT, 0, BRIGHT_RED, 0);
        pause(1);
        square->placeValue(BOLD_FONT, 0, textColor, 0);
        pause(2);
    }
}


void Game::ask()
{
    menu->askForData();
}

void Game::initializeHealthPoints(char path[])
{
    for(int i = 1;i <= healthPoints; ++i)
        table->drawHealthPoints(i, path);
}

void Game::finish(char path[])
{
    int finishWindow = initwindow(END_WINDOW_HEIGHT, END_WINDOW_WIDTH, "End Window", 400, 100);

    setcurrentwindow(finishWindow);
    readimagefile(path, X_LEFT_CORNER, Y_LEFT_CORNER,
                                      END_WINDOW_HEIGHT, END_WINDOW_WIDTH);
    pause(10);
    exit(0);
}

void Game::initializeLightBulb(char path[])
{
    table->drawLightBulb(path);
}

Square * Game::pickRandomCell()
{
    std::vector<Square*> unfilledCells = table->getUnfilledCells();
    int index = Rand(0, unfilledCells.size() - 1);
    return unfilledCells[index];
}

void Game::giveHint()
{
    Square * square = pickRandomCell();

    int value = table->solver->getValueForCell(square->getStartX(), square->getStartY());

    square->setValue(value + '0');
    square->placeValue(BOLD_FONT, 0, textColor, 0);
}
