#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

#include "renderer.h"
Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height)
    : screen_width(screen_width),
      screen_height(screen_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  //Initialize SDL_ttf
  if(TTF_Init()==-1) {
    std::cerr << "TTF_Error: " << TTF_GetError() << "\n";
    exit(2);
  }

  font = TTF_OpenFont("../assets/fonts/charriot.ttf", 32);

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  TTF_Quit();
  SDL_Quit();
}

void Renderer::Render(Player const player, std::vector<Enemy> &enemies) {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  SDL_Rect rect;
  for(auto enemy : enemies)
  {
    if(enemy.GetShow())
    {
      SDL_SetRenderDrawColor(sdl_renderer, 0xE7, 0x38, 0x58, 0xFF);
      rect.w = enemy.GetWidth();
      rect.h = enemy.GetHeight();
      rect.x = static_cast<int>(enemy.GetPosition_x());
      rect.y = static_cast<int>(enemy.GetPosition_y());
      SDL_RenderFillRect(sdl_renderer, &rect);
    }
  }

  // Render player block
  SDL_Rect block;
  block.x = static_cast<int>(player.GetPosition_x());
  block.y = static_cast<int>(player.GetPosition_y());
  block.w = player.GetWidth();
  block.h = player.GetHeight();
  if (player._alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render projectiles
  
  SDL_Rect proy;
  for(auto projectile : player._projectiles)
  {
    SDL_SetRenderDrawColor(sdl_renderer, 0xD9, 0xF3, 0xCF, 0xFF);
    proy.w = projectile.GetWidth();
    proy.h = projectile.GetHeight();
    proy.x = static_cast<int>(projectile.GetPosition_x());
    proy.y = static_cast<int>(projectile.GetPosition_y());
    SDL_RenderFillRect(sdl_renderer, &proy);
  }
  
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::RenderStartGame(int level)
{

  for(size_t i = 3; i>=1; --i){
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);
    std::string game_record = "LEVEL: " + std::to_string(level); 
    RenderRecordText(game_record, 100, 32);
    RenderText(std::to_string(i));
    SDL_RenderPresent(sdl_renderer);
    sleep(1);
  }
}


void Renderer::UpdateWindowTitle(int score, int fps, int seconds) {
  std::string title{"Time Remaining: " + std::to_string(seconds) + "   |   Score: " + std::to_string(score) + "   |   FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}


void Renderer::RenderMenu(Button &start_button, Button &exit_button, std::string level, std::string score, std::string time)
{

   // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
      
  //RENDER GAME RECORD
  std::string game_record = "GAME RECORD";
  RenderRecordText(game_record, 100, 32);
  std::string level_text = "Level: " + level;
  RenderRecordText(level_text, 150, 32);
  std::string score_text = "Score: " + score;
  RenderRecordText(score_text, 200, 32);
  std::string time_text = "Time: " + time; 
  RenderRecordText(time_text, 250, 32);

  SDL_Rect btn;
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  btn.w = start_button.GetWidth();
  btn.h = start_button.GetHeight();
  btn.x = start_button.GetPosition_x();
  btn.y = start_button.GetPosition_y();
  SDL_RenderFillRect(sdl_renderer, &btn);
  
  if( start_button.GetActive())
  {
    
    SDL_Point points[4] = {
      {btn.x - 5, btn.y + btn.h / 2},
      {btn.x - 30, btn.y + 10},
      {btn.x - 30, btn.y + btn.h - 10},
      {btn.x - 5, btn.y + btn.h / 2},
    };

    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(sdl_renderer, points, 4);
  }

  SDL_Rect btn2;
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  btn2.w = exit_button.GetWidth();
  btn2.h = exit_button.GetHeight();
  btn2.x = exit_button.GetPosition_x();
  btn2.y = exit_button.GetPosition_y();
  SDL_RenderFillRect(sdl_renderer, &btn2);

  if(exit_button.GetActive())
  {
    SDL_Point points[4] = {
      {btn2.x - 5, btn2.y + btn2.h / 2},
      {btn2.x - 30, btn2.y + 10},
      {btn2.x - 30, btn2.y + btn2.h - 10},
      {btn2.x - 5, btn2.y + btn2.h / 2},
    };

    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(sdl_renderer, points, 4);
  }
 
  int text_width{0}, text_height{0};
  int posx{0}, posy{0};
  
  std::string start_text = start_button.GetText();
  RenderButtonText(start_text, btn.y, btn.h);

  std::string exit_text = exit_button.GetText();    
  RenderButtonText(exit_text, btn2.y, btn2.h);

  SDL_RenderPresent(sdl_renderer);

}


void Renderer::RenderScore(int score, double time, bool game_over, int level, bool new_record)
{
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  if( game_over)
  {
    std::string score_text = "GAME OVER"; 
    RenderText(score_text);
    SDL_RenderPresent(sdl_renderer);
    sleep(5);
    return;
  }

  if( new_record)
  {
    std::string score_text = "NEW RECORD. CONGRATULATIONS"; 
    RenderRecordText(score_text, 150, 32);
    SDL_RenderPresent(sdl_renderer);
  }

  std::string level_text = "Level: " + std::to_string(level); 
  RenderText(level_text);

  std::string score_text = "Your Score: " + std::to_string(score); 
  RenderText(score_text, 64);

  std::string num_text = std::to_string(time);
  std::string rounded = num_text.substr(0, num_text.find(".")+4);
  std::string time_text = score_text = "Time: " + rounded ; 
  RenderText(time_text, 128);

  SDL_RenderPresent(sdl_renderer);
  sleep(5);

}

void Renderer::RenderText(std::string text, int y)
{
  SDL_Color textColor = {255, 255, 255, 0 };
  SDL_Rect renderQuad;
  int text_width{0}, text_height{0};
  int posx{0}, posy{0};
  textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
  texture = SDL_CreateTextureFromSurface(sdl_renderer, textSurface);
  text_width = textSurface->w;
  text_height = textSurface->h;
  SDL_FreeSurface(textSurface);
  posx = (screen_width / 2)  - text_width / 2;
  posy = (screen_height / 2)  - text_height / 2 + y;
  renderQuad = { posx, posy, text_width, text_height };
  SDL_RenderCopy(sdl_renderer, texture, NULL, &renderQuad);
  SDL_DestroyTexture(texture);
}

void Renderer::RenderButtonText(std::string text, int y, int height)
{
  SDL_Rect renderQuad;
  textSurface = TTF_RenderText_Solid(font, text.c_str(), buttons_text_color);
  texture = SDL_CreateTextureFromSurface(sdl_renderer, textSurface);
  int text_width = textSurface->w;
  int text_height = textSurface->h;
  SDL_FreeSurface(textSurface);
  int posx = (screen_width / 2)  - text_width / 2;
  int posy = y + (height- text_height) / 2;
  renderQuad = { posx, posy, text_width, text_height };
  SDL_RenderCopy(sdl_renderer, texture, NULL, &renderQuad);
  SDL_DestroyTexture(texture);
}

void Renderer::RenderRecordText(std::string text, int y, int height)
{
  SDL_Color text_color = {53, 184, 78, 0 };
  SDL_Rect renderQuad;
  textSurface = TTF_RenderText_Solid(font, text.c_str(), text_color);
  texture = SDL_CreateTextureFromSurface(sdl_renderer, textSurface);
  int text_width = textSurface->w;
  int text_height = textSurface->h;
  SDL_FreeSurface(textSurface);
  int posx = (screen_width / 2)  - text_width / 2;
  int posy = y + (height- text_height) / 2;
  renderQuad = { posx, posy, text_width, text_height };
  SDL_RenderCopy(sdl_renderer, texture, NULL, &renderQuad);
  SDL_DestroyTexture(texture);
}