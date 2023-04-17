#include "table.h"


void Table::initializeSquares()
{
    for(int i = 1; i <= height; ++i)
    {
        for(int j = 1; j <= width; ++j)
        {
            Square * square = new Square(SQUARE_SIZE, SQUARE_SIZE, START_X + (i - 1) * SQUARE_SIZE, START_Y + (j - 1) * SQUARE_SIZE);
            square->setColor(WHITE), square->setBorderColor(LIGHTGRAY, -1);
            square->setValue(gridValues[i][j]);
            squares.push_back(square);

            int subMat = ((i - 1) / 3) * 3 + (j - 1) / 3 + 1;
            sub[subMat].push_back(square);

        }
    }

    settextstyle(BOLD_FONT, 0, 5);
    setbkcolor(GREEN);

    for(int i = 1; i <= height; ++i)
    {
        Square * square = new Square(SQUARE_SIZE, SQUARE_SIZE, START_X + (i - 1) * SQUARE_SIZE, START_Y - SQUARE_SIZE - 10);
        square->setColor(GREEN), square->setBorderColor(BLACK, WHITE);
        squares.push_back(square);
        square->setValue(i + '0');
        specialSquares.push_back(square);
    }

    for(int i = 0; i < squares.size(); ++i)
        squares[i]->init();

    for(int i = 9;i >= 1; --i)
        squares.pop_back();

    for(int i = 0;i < specialSquares.size(); ++i)
        specialSquares[i]->placeValue(BOLD_FONT, 0, BLACK);

    setbkcolor(WHITE);

    for(int i = 0;i < squares.size(); ++i)
        squares[i]->placeValue(BOLD_FONT, 0, BLACK);
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
    std::vector<bool> checker[10];
    for(int i = 1;i <= 9; ++i)
    {
        for(int j = 1;j <= 12; ++j)
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
    std::vector<bool> checker[10];
    for(int i = 1;i <= 9; ++i)
    {
        for(int j = 1;j <= 12; ++j)
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
    for(int i = 1;i <= 9; ++i)
    {
        bool checker[10] = {0};
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
