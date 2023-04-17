#include "solver.h"


Solver::Solver(int height, int width)
{
    foundGrid = false;
    this->height = height;
    this->width = width;
}


bool Solver::checkRow(int row, int value)
{
    if(rowValues[row][value])
        return false;
    return true;
}

bool Solver::checkColumn(int column, int value)
{
    if(columnValues[column][value])
        return false;
    return true;
}

void Solver::prepare()
{
    memset(rowValues, false, sizeof(rowValues));
    memset(columnValues, false, sizeof(columnValues));
}

std::vector<cell> Solver::getGrid()
{
    prepare();
    generatePermutations();

    initializeSubmatrices();
    initializeRemainingCells();

    fillCells(0);
    randomizeGrid();

    return selectedCells;
}


void Solver::randomizeGrid()
{
    int elim = Rand(30, 35);

    bool usedCells[82] = {0};

    while(elim)
    {
        int ind = Rand(0, 80);
        if(usedCells[ind])
            continue;
        selectedCells.push_back(finalGrid[ind]);
        usedCells[ind] = 1;
        elim--;
    }

}

void Solver::initializeRemainingCells()
{
    for(int i = 1; i <= height; ++i)
    {
        for(int j = 1; j <= width; ++j)
        {
            bool ok = 0;
            for(int k = 0; k < leftCorners.size(); ++k)
                ok |= (i >= leftCorners[k].first && i <= leftCorners[k].first + 2 && j >= leftCorners[k].second && j <= leftCorners[k].second + 2);

            if(!ok)
                rmnCells.push_back({i, j, -1});
        }
    }
    numberOfCells = rmnCells.size();

}

void Solver::fillCells(int ind)
{

    if(foundGrid)
        return;

    int currentRow = rmnCells[ind].row, currentColumn = rmnCells[ind].column;

    if(ind < numberOfCells)
    {
        int index = Rand(1, TOTAL_PERMUTATION);

        for(auto j : permutations[index])
        {
            if(!j)
                continue;

            if(foundGrid)
                return;

            bool ok = checkRow(currentRow, j);
            ok &= checkColumn(currentColumn, j);

            if(ok)
            {
                rowValues[currentRow][j] = 1;
                columnValues[currentColumn][j] = 1;
                values[currentRow][currentColumn] = j;
                fillCells(ind + 1);
                rowValues[currentRow][j] = 0;
                columnValues[currentColumn][j] = 0;
            }
        }

    }
    else
    {
        for(int i = 1; i <= height; ++i)
        {
            for(int j = 1; j <= width; ++j)
                finalGrid.push_back({i, j, values[i][j]});
        }
        foundGrid = 1;
    }
}

void Solver::initializeSubmatrices()
{
    for(int i = 0; i < leftCorners.size(); ++i)
    {
        int permutationIndex = Rand(1, TOTAL_PERMUTATION), ind = 0;
        int row = leftCorners[i].first, column = leftCorners[i].second;

        for(int j = row; j <= row + 2; ++j)
        {
            for(int k = column; k <= column + 2; ++k)
            {
                values[j][k] = permutations[permutationIndex][ind++];
                rowValues[j][values[j][k]] = columnValues[k][values[j][k]] = 1;
            }
        }
    }
}

void Solver::generatePermutations()
{
    for(int i = 1; i <= 9; ++i)
        perm[i] = i;

    int contor = 1;
    while(std::next_permutation(perm + 1, perm + 10))
    {
        for(int i = 1; i <= 9; ++i)
            permutations[contor].push_back(perm[i]);
        contor++;
    }
}

std::vector<cell> Solver::getSolution()
{
    finalGrid.clear();

    for(int i = 1;i <= height; ++i)
    {
        for(int j = 1;j <= width; ++j)
        {
            bool ok = 0;
            for(int k = 0;k < selectedCells.size(); ++k)
                ok |= (selectedCells[k].row == i && selectedCells[k].column == j);

            if(!ok)
                finalGrid.push_back({i, j, values[i][j]});
        }
    }

    return finalGrid;
}
