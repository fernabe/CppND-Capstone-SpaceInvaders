#include <iostream>
#include "player.h"

Player::Player(int screen_width, int screen_height) : Rectangle(RectangleType::rectanglePlayer, screen_width, screen_height, 10.0, 20, 20)
{

}

void Player::UpdatePosition(int screen_width)
{   
    float right_limit = static_cast<float>( screen_width ) -_width;
    switch ( _direction ) 
    {
        case Direction::kLeft:
        if( _position_x > 0)
            _position_x -= _speed;
        break;

        case Direction::kRight:
        if( _position_x < right_limit) 
            _position_x += _speed;
        break;
    }

    _direction = Direction::kNone;
}


void Player::UpdateProjectiles()
{
    for (auto it = _projectiles.begin(); it != _projectiles.end();)
    {
        if ( it->GetPosition_y() < 0)
            it = _projectiles.erase(it);
        else
        {
            it->UpdatePosition();
            ++it;
        }     
    } 
}