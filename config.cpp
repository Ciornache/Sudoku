#include "config.h"


int Rand(int a, int b)
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int ans = uniform_int_distribution<int>(a, b)(rng);
}
