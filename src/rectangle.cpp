#include "rectangle.h"
#include <iostream>

Rectangle::Rectangle(RectangleType type, int screen_width, int screen_height, float speed, int width, int height) 
    : _rectangle_type(type), 
    _speed(speed),
    _position_x(screen_width/2),
    _position_y(screen_width - height * 2),
    _width(width),
    _height(height)
{

}


Rectangle::Rectangle(RectangleType type, float speed, int width, int height, float pos_x, float pos_y)
    : _rectangle_type(type), 
    _speed(speed),
    _position_x(pos_x),
    _position_y(pos_y),
    _width(width),
    _height(height)
{
    
}