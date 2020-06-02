#include <SDL2/SDL.h>

#include "controller.h"
#include "projectile.h"


void Controller::ChangeDirection(Player &player, Player::Direction input, Player::Direction opposite) const 
{
    if (player._direction != opposite) 
    {
        player._direction = input;
    }
    
    return;
}

void Controller::HandleInput(bool &exit_game, bool &running, Player &player) const {
    SDL_Event e;
    
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) 
        {
            running = false;
            exit_game = true;
        }
        else if (e.type == SDL_KEYDOWN) 
        {
            switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                ChangeDirection(player, Player::Direction::kLeft,
                                Player::Direction::kRight);
                break;

                case SDLK_RIGHT:
                ChangeDirection(player, Player::Direction::kRight,
                                Player::Direction::kLeft);
                break;

                case SDLK_SPACE:
                    float x = player.GetPosition_x() + (player.GetWidth() / 2) ;
                    float y = player.GetPosition_y() ;
                    Projectile p{x, y};
                    player._projectiles.push_back(p);
                break; 
            }
        }
    }
}
void Controller::HandleInput(Button &btn, Button &btn2, bool &start, bool &quit_game)  {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
           
        if (e.type == SDL_QUIT) 
        {
            quit_game = true;
        }
        else if (e.type == SDL_KEYDOWN) 
        {
            switch (e.key.keysym.sym) {
              
                case SDLK_UP:
                    if(!btn.GetActive())
                    {
                        btn2.SetActive(false);
                        btn.SetActive(true);
                    }
                break;

                case SDLK_DOWN:
                    if( !btn2.GetActive())
                    {   
                        btn.SetActive(false);
                        btn2.SetActive(true);
                    }
                break;

                case SDLK_RETURN:
    
                    if( btn.GetActive())
                        start = true;
                    
                    if(btn2.GetActive())
                        quit_game = true;

                break;
            }
        }
    }
}