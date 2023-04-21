#include "table.h"


void Table::initializeSquares()
{
    for(int i = 1; i <= height; ++i)
    {
        for(int j = 1; j <= width; ++j)
        {
            Square * square = new Square(SQUARE_SIZE, SQUARE_SIZE, START_X + (i - 1) * SQUARE_SIZE, START_Y + (j - 1) * SQUARE_SIZE);
            square->setColor(squareColor), square->setBorderColor(borderColor, -1);
            square->setValue(gridValues[i][j]);
            squares.push_back(square);

            int sqr = sqrt(height), subMat = ((i - 1) / sqr) * sqr + (j - 1) / sqr + 1;
            sub[subMat].push_back(square);
        }
    }

    settextstyle(BOLD_FONT, 0, 5);

    for(int i = 1; i <= height; ++i)
    {
        Square * square = new Square(SQUARE_SIZE, SQUARE_SIZE, START_X + (i - 1) * SQUARE_SIZE, START_Y - SQUARE_SIZE - 10);
        square->setColor(upperSquareColor), square->setBorderColor(borderColor, WHITE);
        squares.push_back(square);
        square->setValue(i + '0');
        specialSquares.push_back(square);
    }

    for(int i = 0; i < squares.size(); ++i)
        squares[i]->init();

    for(int i = height;i >= 1; --i)
        squares.pop_back();

    for(int i = 0;i < specialSquares.size(); ++i)
        specialSquares[i]->placeValue(BOLD_FONT, 0, textColor, 1);

    for(int i = 0;i < squares.size(); ++i)
        squares[i]->placeValue(BOLD_FONT, 0, textColor, 0);
}

void Table::initializeValues()
{
    solver = new Solver(height, width);
    values = solver->getGrid();

    for(int i = 1;i <= height; ++i)
    {
        for(int j = 1;j <= width; ++j)
            gridValues[i][j] = ' ';
    }

    for(int j = 0;j < values.size(); ++j)
        gridValues[values[j].column][values[j].row] = values[j].value + '0';

    if(textColor == -1)
        textColor = BLACK;

    if(squareColor == -1)
        squareColor = WHITE;

    if(upperSquareColor == -1)
        upperSquareColor = GREEN;

    if(borderColor == -1)
        borderColor = LIGHTGRAY;
}

void Table::init()
{
    this->initializeValues();
    this->initializeSquares();
    this->drawTableBorders();
}

void Table::drawTableBorders()
{
    int sqr = sqrt(height);

    setcolor(BLACK);
    settextstyle(BOLD_FONT, 0, 5);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);


    for(int i = 1; i <= sqr; ++i)
    {
        for(int j = 1; j <= sqr; ++j)
        {
            int SUBMATRIX_SIZE = sqr * SQUARE_SIZE;

            int start_x = START_X + (i - 1) * SUBMATRIX_SIZE;
            int start_y = START_Y + (j - 1) * SUBMATRIX_SIZE;

            line(start_x, start_y,
                 start_x, start_y + SUBMATRIX_SIZE);
            line(start_x, start_y,
                 start_x + SUBMATRIX_SIZE, start_y);
            line(start_x, start_y + SUBMATRIX_SIZE,
                 start_x + SUBMATRIX_SIZE, start_y + SUBMATRIX_SIZE);
            line(start_x + SUBMATRIX_SIZE, start_y,
                 start_x + SUBMATRIX_SIZE, start_y + SUBMATRIX_SIZE);
        }
    }
}

Square * Table::findSquare(int x, int y)
{
    for(int i = 0; i < squares.size(); ++i)
    {
        int start_x = squares[i]->getStartX();
        int start_y = squares[i]->getStartY();

        int leftRow = start_x + SQUARE_SIZE - 1;
        int leftColumn = start_y + SQUARE_SIZE - 1;
        if(x >= start_x && x <= leftRow && y >= start_y && y <= leftColumn)
            return squares[i];
    }
    return NULL;
}

Square * Table::findSpecialSquare(int x, int y)
{
    for(int i = 0; i < specialSquares.size(); ++i)
    {
        int start_x = specialSquares[i]->getStartX();
        int start_y = specialSquares[i]->getStartY();

        int leftRow = start_x + SQUARE_SIZE;
        int leftColumn = start_y + SQUARE_SIZE;

        if(x >= start_x && x <= leftRow && y >= start_y && y <= leftColumn)
            return specialSquares[i];
    }
    return NULL;
}

void Table::print()
{
    for(int i = 0; i < squares.size(); ++i)
        std::cout << squares[i]->getStartX() << ' ' << squares[i]->getStartY() << '\n';
    std::cout << '\n';
}

bool Table::checkRows()
{
    std::vector<bool> checker[NUMBER_OF_VALUES + 5];
    for(int i = 1;i <= height; ++i)
    {
        for(int j = 1;j <= NUMBER_OF_VALUES + 1; ++j)
            checker[i].push_back(0);
    }
    for(int i = 0;i < squares.size(); ++i)
    {
        int row = (squares[i]->getStartX() - START_X) / SQUARE_SIZE + 1;
        char value = squares[i]->getValue();
        if(value != ' ')
        {
            if(checker[row][value - '0'])
                return false;
            checker[row][value - '0'] = 1;
        }
    }
    return true;
}

bool Table::checkColumns()
{
    std::vector<bool> checker[NUMBER_OF_VALUES + 5];
    for(int i = 1;i <= 9; ++i)
    {
        for(int j = 1;j <= NUMBER_OF_VALUES + 1; ++j)
            checker[i].push_back(0);
    }

    for(int i = 0;i < squares.size(); ++i)
    {
        int column = (squares[i]->getStartY() - START_Y) / SQUARE_SIZE + 1;

        char value = squares[i]->getValue();

        if(value != ' ')
        {
            if(checker[column][value - '0'])
                return false;
            checker[column][value - '0'] = 1;
        }
    }
    return true;
}

bool Table::checkSubmatrixes()
{
    for(int i = 1;i <= NUMBER_OF_VALUES; ++i)
    {
        bool checker[NUMBER_OF_VALUES + 5] = {0};
        for(auto j : sub[i])
        {
            char value = j->getValue();

            if(value != ' ')
            {
                if(checker[value - '0'])
                    return false;
                checker[value - '0'] = 1;
            }
        }
    }
    return true;
}

bool Table::checkGrid()
{
//    std::cout << this->checkColumns() << ' ' << this->checkSubmatrixes() << ' ' << this->checkRows() << '\n';

    return this->checkColumns() && this->checkSubmatrixes()
                    && this->checkRows();
}

void Table::drawHealthPoints(int index, char path[])
{
    heartLeftCorners.push_back({HEALTH_UPPER_X + (index - 1) * HEALTH_OFFSET, HEALTH_UPPER_Y});
    heartRightCorners.push_back({HEALTH_LOWER_X + (index - 1) * HEALTH_OFFSET, HEALTH_LOWER_Y});

    readimagefile(path, HEALTH_UPPER_X + (index - 1) * HEALTH_OFFSET, HEALTH_UPPER_Y,
                               HEALTH_LOWER_X + (index - 1) * HEALTH_OFFSET, HEALTH_LOWER_Y);
}

void Table::removeHeart(int index)
{
    readimagefile("props/black.jpg", heartLeftCorners[index - 1].first, heartLeftCorners[index - 1].second,
                               heartRightCorners[index - 1].first, heartRightCorners[index - 1].second);
}

void Table::drawLightBulb(char path[])
{
    readimagefile(path, BULB_UPPER_X, BULB_UPPER_Y,
                        BULB_LOWER_X, BULB_LOWER_Y);
}

std::vector<Square*> Table::getUnfilledCells()
{
    std::vector<Square*> unfilledCells;

    for(int i = 0;i < squares.size(); ++i)
    {
        if(squares[i]->getValue() == ' ')
            unfilledCells.push_back(squares[i]);
    }
    return unfilledCells;
}

bool Table::checkLightBulb(int xCoordinate, int yCoordinate)
{
    return xCoordinate >= BULB_UPPER_X && xCoordinate <= BULB_LOWER_X &&
          yCoordinate >= BULB_UPPER_Y && yCoordinate <= BULB_LOWER_Y;
}

bool Table::isEmpty()
{
    for(int i = 0;i < squares.size(); ++i)
    {
        if(squares[i]->getValue() == ' ')
            return false;
    }
    return true;
}
