#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "rectangle.h"

class Projectile :  public Rectangle
{
    public:
        Projectile();
        Projectile(float x, float y);
        void UpdatePosition() override;
    private:

};

#endif