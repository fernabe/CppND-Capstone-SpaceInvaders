#include <fstream>
#include <sstream>


#include "renderer.h"
#include "controller.h"
#include "game.h"
#include "player.h"
#include "button.h"

int main() {
  
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};

  Renderer renderer(kScreenHeight, kScreenHeight);
  Controller controller;

  Button start_button{kScreenWidth / 2 - kScreenWidth / 2 / 2, kScreenWidth/2, "START", true};
  Button exit_button{kScreenWidth / 2 - kScreenWidth / 2 / 2, kScreenWidth/2 + 42  , "QUIT GAME", false};
  
  bool start{false};
  bool quit_game{false};

  Game game(kScreenWidth, kScreenHeight);

  std::string line;
  std::string level;
  std::string record;
  std::string time;

  while(!game.GetExitGame() )
  { 
    std::ifstream stream("../assets/game_scores/records.txt");

    if (stream.is_open()) {
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> level >>record >> time;
    }
    
    stream.close();

    if( record.empty() )
    {
      level = "0";
      record = "0";
      time = "0.0";
    }
  
    SDL_PumpEvents();
    SDL_FlushEvents(SDL_KEYDOWN, SDL_KEYUP);

    while (!start && !quit_game)
    { 
      renderer.RenderMenu(start_button, exit_button, level, record, time);
      controller.HandleInput(start_button, exit_button, start, quit_game);
    }
   
    if(start)
    { 
      start = false;
      game.Run(controller, renderer, kMsPerFrame);
      game.Reset(); 
    }

    else
      break;
  } 

  return 0;
}
