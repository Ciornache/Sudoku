#ifndef CONFIG_H
#define CONFIG_H

#include <string.h>
#include <algorithm>
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
#define START_Y 200
#define TABLE_WIDTH 9
#define TABLE_HEIGHT 9
#define X_BUFFER 14
#define Y_BUFFER 8
#define BRIGHT_RED COLOR(255, 0, 0)
#define NUMBER_OF_VALUES 9

#define HEALTH_UPPER_Y 65
#define HEALTH_LOWER_Y 115
#define HEALTH_OFFSET 70
#define HEALTH_UPPER_X 250
#define HEALTH_LOWER_X 300

#define BULB_UPPER_Y 20
#define BULB_LOWER_Y 70
#define BULB_UPPER_X 20
#define BULB_LOWER_X 70

#define END_WINDOW_HEIGHT 600
#define END_WINDOW_WIDTH 600
#define X_LEFT_CORNER 0
#define Y_LEFT_CORNER 0


#define MINIMUM_NUMBER_OF_CELLS 35
#define MAXIMUM_NUMBER_OF_CELLS 45
#define TOTAL_PERMUTATION 362880
#define SECONDS_BUFFER 300000000
#define GENERATE_METHOD 1

using namespace std;

int Rand (int a, int b);

void rotateRight(int a[]);
void pause(int seconds);


extern int squareColor, upperSquareColor, textColor,
    type, difficulty;

struct cell
{
    int row;
    int column, value = -1;
};


#endif // CONFIG_H
