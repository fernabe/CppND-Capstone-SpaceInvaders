#ifndef ENEMY_H
#define ENEMY_H

#include "rectangle.h"

class Enemy : public Rectangle
{
    private:
        bool _onScreen{false};
        bool _collision;
    public:
        Enemy(float x, float y, float speed);
        ~Enemy(){};
        void UpdatePosition() override;
        void SetShow(bool show);
        bool GetShow();
        void SetCollision(bool collision);
        bool GetCollision();
};

#endif