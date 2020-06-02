#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "player.h"
#include "enemy.h"
#include "button.h"


class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();
  void Render(Player player, std::vector<Enemy> &enemies);
  void RenderStartGame(int level);
  void RenderMenu(Button &start, Button &exit, std::string level, std::string score, std::string time);
  void RenderScore(int score, double time, bool game_over, int level, bool new_record);
  void UpdateWindowTitle(int score, int fps, int seconds);
  void RenderText(std::string text, int y = 0);
  void RenderButtonText(std::string text, int y, int height);
  void RenderRecordText(std::string text, int y, int height);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  const std::size_t screen_width;
  const std::size_t screen_height;
  TTF_Font *font;
  SDL_Color buttons_text_color = {255, 255, 255, 0 };
  SDL_Surface* textSurface = NULL;
  SDL_Texture* texture = NULL;
};

#endif
