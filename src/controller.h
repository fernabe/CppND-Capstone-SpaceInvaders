#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "button.h"

class Controller {
    
    public:
    void HandleInput(bool &exit_game,bool &running, Player &player) const;
    void HandleInput(Button &btn, Button &btn2, bool &start, bool &quit_game) ;

    private:
    void ChangeDirection(Player &player, Player::Direction input,
                        Player::Direction opposite) const;
    
};

#endif