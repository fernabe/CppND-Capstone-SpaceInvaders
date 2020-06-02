#include "button.h"

Button::Button(int x, int y, std::string text, bool active) 
    : _position_x(x),
      _position_y(y), 
      _text(text),
      _active(active)
{
    
}