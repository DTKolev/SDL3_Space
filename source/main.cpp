#include "SpaceHeader.hpp"

int main() {
  SpaceGame space_game;
  
  space_game.GameInit();
  space_game.GameRun();
  space_game.GameTerminate();

  return 0;
}