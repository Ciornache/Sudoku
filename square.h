#ifndef SQUARE_H
#define SQUARE_H


#include "config.h"

class Square
{

public:

    Square(int h, int w, int x, int y) : height(h), width(w), start_x(x), start_y(y) {};
    ~Square() = default;

    void setColor(int color);
    void setBorderColor(int color, int alternant);
    void setValue(char ch);

    void init();
    void placeValue(int font, int direction, int color, bool type);

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
