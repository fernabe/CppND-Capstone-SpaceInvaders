#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <SDL2/SDL.h>

class Button
{
    public:
        Button(int x, int y, std::string text, bool active);
        int GetPosition_x(){ return _position_x; }
        int GetPosition_y(){ return _position_y; }
        int GetWidth(){ return _width; }
        int GetHeight(){ return _height; }
        std::string GetText(){ return std::string(_text); }
        void SetActive(bool active){_active = active;}
        bool GetActive(){ return _active;}

    private:
        int _position_x;
        int _position_y;
        int _width{320};
        int _height{32};
        std::string _text;
        bool _active;
};
#endif