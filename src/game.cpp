#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>

#include "game.h"

#include <SDL2/SDL.h>

Game::Game(std::size_t screen_width, std::size_t screen_height)
    :   _screen_width(screen_width),
        _screen_heigth(screen_height), 
        _player(screen_width, _screen_heigth ),
        engine(dev()),
        random_w(10, screen_width - 10)
{
    number_of_enemies = number_of_enemies;
    CreateEnemies();
}

Game::~Game()
{

}

void Game::Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration)
{
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;

    _exit_game = false;

    bool running = true;
    
    int counter = 0;
    int a = 0;

    auto game_start = std::chrono::system_clock::now();
   
    renderer.RenderStartGame(_level);

    while (running) {
        
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        
        controller.HandleInput(_exit_game, running, _player);
    
        Update();

        if(counter == a + seconds_between_enemies)
        {
            for(auto &enemy : _enemies)
            {
                if( !enemy.GetShow())
                {
                    enemy.SetShow(true);
                    break;
                }
            }
            a += seconds_between_enemies;
        }
        
        renderer.Render(_player, _enemies);
    

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        frame_duration = frame_end - frame_start;
       
        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000) {
           
            renderer.UpdateWindowTitle(_score, frame_count, _countdown);
            
            frame_count = 0;
            title_timestamp = frame_end;

            counter++;
            _countdown--;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }

        if(_countdown < 0 || _enemies.size() == 0 || _game_over)
        {   
            auto game_end = std::chrono::system_clock::now();
            std::chrono::duration<float,std::milli> duration = game_end - game_start;
            double time = duration.count() / 1000;
            time = round( time * 1000.0 ) / 1000.0;
            
            if( _countdown < 0)
                _countdown = 0;

            renderer.RenderScore(_score, time, _game_over, _level, CheckRecord(time));

            if(_score == number_of_enemies)
            {
                ++_level;
                _speed_enemy += 0.5;
            }
            if( _game_over )
            {   
                _level = 1;
                _speed_enemy = 2.0;
            }

            running = false;
        }   
    }
}

void Game::CreateEnemies()
{
    for(size_t i = 0; i < number_of_enemies ; i++ ){

        int x = random_w(engine);
        while( x % 10 != 0)
        {   
            if( x % 10 == 0 )
                break;

            x = random_w(engine);
        }  
        x -= 3;
        float position_x = static_cast<float>(x);
        float position_y = 0.0f;
        Enemy enemy{position_x, position_y, _speed_enemy};
        _enemies.push_back(enemy);
    }
}

void Game::UpdateEnemies()
{
    for (auto it = _enemies.begin(); it != _enemies.end();)
    {
        if( !it->GetShow() )
            return;
        if ( it->GetPosition_y() > 640)
            it = _enemies.erase(it);
        else
        {
            it->UpdatePosition();
            ++it;
        }     
    } 
}

void Game::CheckCollisions()
{
    for (int i = 0; i < _player._projectiles.size(); i++)
    {
        for (int j = 0; j < _enemies.size(); j++)
        {
            if( _enemies[j].GetShow())
            {
                if (CheckEnemyProjectilCollision(_player._projectiles[i], _enemies[j]))
                {
                    _player._projectiles.erase(_player._projectiles.begin() + i);
                    _enemies.erase(_enemies.begin() + j);
                    ++_score;
                    return;
                }
            }
        }
    }

    for(auto &enemy : _enemies)
    {
        if( enemy.GetShow())
        {
            if( enemy.GetPosition_y() >= _player.GetPosition_y())
            {   
                if( CheckEnemyPlayerCollision(enemy))
                {
                    _game_over = true;
                    return;
                }
            }
        }
    }

}

void Game::Update() 
{   
    _player.UpdatePosition(_screen_width);
    _player.UpdateProjectiles();
    UpdateEnemies();
    CheckCollisions();
}

int Game::GetScore() const { return _score; }

bool Game::CheckEnemyProjectilCollision(Projectile &projectile, Enemy &enemy)
{

    int projectileRight = static_cast<int>(projectile.GetPosition_x());
    int enemyRight = static_cast<int>(enemy.GetPosition_x());

    int projectileTop = static_cast<int>(projectile.GetPosition_y());
    int enemyTop = static_cast<int>(enemy.GetPosition_y());

    if (projectileRight - 3 != enemyRight) {
        return false;
    }

    if (projectileTop > enemyTop ) {
        return false;
    }

    //If collision
    return true;
}

bool Game::CheckEnemyPlayerCollision(Enemy &enemy)
{

    int enemyLeft = static_cast<int>(enemy.GetPosition_x());
    int playerLeft = static_cast<int>(_player.GetPosition_x());

    int enemyRight = static_cast<int>(enemy.GetPosition_x() + enemy.GetWidth());
    int playerRight = static_cast<int>(_player.GetPosition_x() + _player.GetWidth());

    if( enemyLeft >= playerLeft && enemyLeft <= playerRight )
        return true;
    
    if( enemyRight >= playerLeft && enemyRight <= playerRight )
        return true;

    return false;
}


void Game::Reset()
{
    _score = 0;
    _enemies.clear();
    CreateEnemies();
    _countdown = 40;
    float x = _screen_width / 2;
    float y = _screen_heigth - _player.GetHeight() - 10;
    _player.SetPosition_x(_screen_width / 2);
    _player.SetPosition_y(_screen_heigth - _player.GetWidth() - 10 );
    _player._projectiles.clear();
    _game_over = false;
}

bool Game::CheckRecord(double time)
{
    
    if(_game_over)
        return false;

    std::string line;
    std::ifstream stream("../assets/game_scores/records.txt");
    std::string level;
    std::string record;
    std::string time_record;

    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> level >>record >> time_record;
    }
    stream.close();

    if( record.empty() )
    {
        level = "0";
        record = "0";   
        time_record = "0.0";
    }

    if( _level > std::stoi(level))
    {
        SaveRecord(time);
        return true;
    }

    if( _level == std::stoi(level) && _score > std::stoi(record))
    {
        SaveRecord(time);
        return true;
    }

    if( _level == std::stoi(level) && _score == std::stoi(record) && time < std::stod(time_record))
    {
        SaveRecord(time);
        return true;
    }

    return false;
}

void Game::SaveRecord(double time)
{
    std::ofstream stream("../assets/game_scores/records.txt");
    if (stream.is_open()) {
        stream << _level << " " << _score << " " << time;   
    } 
    stream.close();
}