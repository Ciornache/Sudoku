#include "config.h"

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int Rand(int a, int b)
{
    int ans = uniform_int_distribution<int>(a, b)(rng);
    return ans;
}

int squareColor, upperSquareColor, textColor,
    type, difficulty, borderColor;

void rotateRight(int a[])
{
    for(int i = NUMBER_OF_VALUES; i > 1; --i)
        swap(a[i], a[i - 1]);
}

void pause(int seconds)
{
    int realSeconds = seconds * SECONDS_BUFFER;
    while(realSeconds)
        realSeconds--;
}
