#include "square.h"



void Square::setColor(int color)
{
    square_color = color;
}

void Square::setBorderColor(int color, int alternant)
{
    border_color = color;
    alternativeBorder = alternant;
}

void Square::drawSquare()
{
    int goodBorder = border_color;

    setfillstyle(SOLID_FILL, square_color);
    setcolor(border_color);

    if(alternativeBorder != -1)
        setcolor(alternativeBorder), goodBorder = alternativeBorder;

    line(start_x, start_y,
         start_x, start_y + width);
    line(start_x, start_y,
         start_x + height, start_y);
    line(start_x, start_y + width,
         start_x + height, start_y + width);
    line(start_x + height, start_y,
         start_x + height, start_y + width);

    floodfill(start_x + 1, start_y + 1, goodBorder);
}

void Square::drawBorders()
{
    settextstyle(BOLD_FONT, 0, 5);
    setcolor(border_color);

    line(start_x, start_y,
         start_x, start_y + width);
    line(start_x, start_y,
         start_x + height, start_y);
    line(start_x, start_y + width,
         start_x + height, start_y + width);
    line(start_x + height, start_y,
         start_x + height, start_y + width);
}

void Square::init()
{
    drawSquare();
    drawBorders();
}

void Square::setValue(char ch)
{
    value = ch;
}

char Square::getValue()
{
    return value;
}

int Square::getStartX()
{
    return start_x;
}

int Square::getStartY()
{
    return start_y;
}

void Square::placeValue(int font, int direction, int color, bool squareType)
{
    char text[2];
    text[0] = value, text[1] = '\0';

    setcolor(color);
    settextstyle(font, direction, 5);

    if(squareType)
        setbkcolor(upperSquareColor);
    else
        setbkcolor(squareColor);

    outtextxy(start_x  + X_BUFFER, start_y + Y_BUFFER, text);
}
