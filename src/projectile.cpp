#include "projectile.h"

Projectile::Projectile(float x, float y) 
    : Rectangle(RectangleType::rectangleProjectile, 7.5, 2, 10, x, y)
{

}

void Projectile::UpdatePosition()
{   
    _position_y = _position_y - _speed;
}