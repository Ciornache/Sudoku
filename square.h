#ifndef SQUARE_H
#define SQUARE_H


#include "config.h"

class Square
{

public:
    Square(int h, int w, int x, int y) : height(h), width(w), start_x(x), start_y(y) {};
    void setColor(int color);
    void setBorderColor(int color, int alternant);
    void init();
    void setValue(char ch);
    void placeValue(int font, int direction, int color);

    char getValue();

    int getStartX();
    int getStartY();

private:

    char value = ' ';
    int height, width;
    int start_x, start_y;
    int square_color, border_color, alternativeBorder;

    void drawSquare();
    void drawBorders();

};


#endif // SQUARE_H
