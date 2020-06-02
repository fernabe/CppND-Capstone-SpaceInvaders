#ifndef RECTANGLE_H
#define RECTANGLE_H


enum RectangleType
{
    rectanglePlayer,
    rectangleEnemy,
    rectangleProjectile
};

class Rectangle
{
    public:

        Rectangle(RectangleType type, int screen_width, int screen_height, float speed, int width, int height);
        Rectangle(RectangleType type, float speed, int width, int height, float pos_x, float pos_y);

        //Setters
        void SetPosition_x(float x){ _position_x = x; }
        void SetPosition_y(float y){ _position_y = y; }

        //Getters
        RectangleType GetType() const { return _rectangle_type; }
        int GetScreenWidth() const{ return _screen_width; };
        int GetScreenHeight() const{ return _screen_height; };
        float GetPosition_x() const { return _position_x; };
        float GetPosition_y() const { return _position_y; };
        int GetWidth() const { return _width; };
        int GetHeight() const { return _height; }
        float GetSpeed() const { return _speed; }
        virtual void UpdatePosition(){};
        virtual void UpdatePosition(int screen_size){};

    protected:
        /* data */
        RectangleType _rectangle_type;

        int _screen_width;
        int _screen_height;
        float _position_x;
        float _position_y;
        int _width;
        int _height;
        float _speed;
        bool _show_in_screen;
};

#endif