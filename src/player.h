#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "projectile.h"

class Player : public Rectangle
{
    public:

        enum class Direction { kNone, kLeft, kRight };
        Player(int screen_width, int screen_height);
        Direction _direction = Direction::kNone;
        bool _alive{true};
        
        std::vector<Projectile> _projectiles;
        void UpdatePosition(int screen_width) override;
        void UpdateProjectiles();

    private:
        
};
#endif