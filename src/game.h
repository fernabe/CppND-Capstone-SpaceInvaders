#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include <SDL2/SDL.h>

#include "controller.h"
#include "renderer.h"
#include "player.h"
#include "enemy.h"

class Game {
  public:
    Game(std::size_t screen_size,  std::size_t screen_height);
    ~Game();
    void Reset();
    void Run(Controller const &controller, Renderer &renderer,
            std::size_t target_frame_duration);
    int GetScore() const;
    int GetSize() const;
    bool GetExitGame() const {return _exit_game; };
    
  private:

    Player _player;

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;

    int _screen_width;
    int _screen_heigth;
    int _level{1};
    float _speed_enemy{2.0};
    int _score{0};
    int _countdown{40};
    bool _game_over{false};
    bool _exit_game{false};
    float seconds_between_enemies{2};
    int number_of_enemies{15};
    std::vector<Enemy> _enemies;
    
    void Update();
    void CreateEnemies();
    void UpdateEnemies();
    void CheckCollisions();
    bool CheckEnemyProjectilCollision(Projectile &projectile, Enemy &enemy);
    bool CheckEnemyPlayerCollision(Enemy &Enemy);
    bool CheckRecord(double time);
    void SaveRecord(double time);
};

#endif