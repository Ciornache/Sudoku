#ifndef H_SOLVER
#define H_SOLVER


#include "config.h"


class Solver
{

public:
    Solver(int height, int width);

    std::vector<cell> getGrid();
    std::vector<cell> getSolution();

    void initializeGrid();
    void solveGrid();

    int getValueForCell(int row, int column);

private:

    bool foundGrid;

    std::vector<int> permutations[TOTAL_PERMUTATION + 5];

    int height, width, numberOfCells;
    int perm[NUMBER_OF_VALUES + 5], permIndexes[TOTAL_PERMUTATION + 5];
    int values[NUMBER_OF_VALUES + 5][NUMBER_OF_VALUES + 5];
    int chosenPermutation[NUMBER_OF_VALUES + 5];

    std::vector<pair<int,int>> leftCorners = {{1, 1},
                                              {4, 4},
                                              {7, 7}};

    std::vector<cell> selectedCells, rmnCells;
    std::vector<cell> finalGrid;

    void randomizeGrid();
    void generateGrid(int ind);
    void generatePermutations();

    void initializeSubmatrices();
    void initializeRemainingCells();

    void prepare();
    void getRemainingCells();

    void fillCells(int);
    void fillGrid2();

    bool rowValues[NUMBER_OF_VALUES + 5][NUMBER_OF_VALUES + 5], columnValues[NUMBER_OF_VALUES + 5][NUMBER_OF_VALUES + 5],
         subValues[NUMBER_OF_VALUES + 5][NUMBER_OF_VALUES + 5];

    bool checkRow(int row, int value);
    bool checkColumn(int column, int value);
    bool checkGrid(int sub, int value);
    bool checkSub(int sub, int value);

};


#endif // H_SOLVER
