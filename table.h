#ifndef H_TABLE
#define H_TABLE

#include "square.h"
#include "solver.h"

class Table
{
public:
    Table(int height, int width) : height(height), width(width) {};
    void init();
    Square * findSquare(int x, int y);
    void print();
    Square * findSpecialSquare(int x, int y);

    bool checkGrid();

    Solver * solver;

private:

    char gridValues[10][10];

    int height, width;
    std::vector<Square*> squares, specialSquares;
    std::vector<Square*> sub[10];

    std::vector<cell> values;

    void initializeValues();
    void initializeSquares();
    void drawTableBorders();

    bool checkRows();
    bool checkColumns();
    bool checkSubmatrixes();

};



#endif // H_TABLE
