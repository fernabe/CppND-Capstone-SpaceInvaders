#include <iostream>
#include "enemy.h"
#include "rectangle.h"

Enemy::Enemy(float x, float y, float speed) 
    : Rectangle(RectangleType::rectangleEnemy, speed , 8, 8, x, y)
{
}

void Enemy::UpdatePosition()
{   
    _position_y += +_speed;
}

void Enemy::SetShow(bool show)
{
    _onScreen= show;
}

bool Enemy::GetShow()
{
    return _onScreen;
}

void Enemy::SetCollision(bool collision)
{
    this->_collision = collision;
}

bool Enemy::GetCollision()
{
    return this->_collision;
}