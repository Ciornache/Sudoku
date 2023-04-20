#ifndef H_TABLE
#define H_TABLE

#include "square.h"
#include "solver.h"

class Table
{
public:

    Table(int height, int width) : height(height), width(width) {};
    ~Table() = default;

    void init();
    Square * findSquare(int x, int y);
    void print();
    Square * findSpecialSquare(int x, int y);

    std::vector<Square*> getUnfilledCells();

    void drawLightBulb(char path[]);

    void drawHealthPoints(int index, char path[]);
    void removeHeart(int index);

    bool checkGrid();
    bool checkLightBulb(int xCoordinate, int yCoordinate);
    bool isEmpty();

    Solver * solver;

private:

    char gridValues[NUMBER_OF_VALUES + 5][NUMBER_OF_VALUES + 5];

    int height, width;

    std::vector<Square*> squares, specialSquares;
    std::vector<Square*> sub[NUMBER_OF_VALUES + 5];

    std::vector<cell> values;

    std::vector<std::pair<int,int>> heartLeftCorners, heartRightCorners;

    void initializeValues();
    void initializeSquares();

    void drawTableBorders();

    bool checkRows();
    bool checkColumns();
    bool checkSubmatrixes();
};



#endif // H_TABLE
