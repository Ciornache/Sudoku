#ifndef CONFIG_H
#define CONFIG_H

#include <bits/stdc++.h>
#include <cmath>
#include <graphics.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <random>

#define SQUARE_SIZE 50
#define START_X 125
#define START_Y 125
#define TABLE_WIDTH 9
#define TABLE_HEIGHT 9
#define X_BUFFER 14
#define Y_BUFFER 8
#define BRIGHT_RED COLOR(255, 0, 0)

#define MINIMUM_NUMBER_OF_CELLS 35
#define MAXIMUM_NUMBER_OF_CELLS 45
#define TOTAL_PERMUTATION 362880
#define SECONDS_BUFFER 300000000

using namespace std;

int Rand (int a, int b);

struct cell
{
    int row;
    int column, value = -1;
};


#endif // CONFIG_H
