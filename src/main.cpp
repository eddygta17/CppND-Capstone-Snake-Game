#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    std::cout << "You should print your username as a parameter." << std::endl;
    return 1;
  }
    
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  
  //passing username into game constructor
  Game game(kGridWidth, kGridHeight, argv[1]);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Player Name : " << game.GetName() << "\n";
  if(game.GetScore() > game.GetRecord())
  {
  	std::cout << "New record score: " << game.GetScore() << "\n";
    game.SetRecord();
  }
  else
  {
    std::cout << "Score: " << game.GetScore() << "\n";
    std::cout << "Record score: " << game.GetRecord() << "\n";
  }
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}