#include "SpaceHeader.hpp"

int main() {
  std::cout << "Program is running\n";
  SpaceGame space_game;
  std::cout << "Tried to initialize Space Game\n";
  space_game.GameInit();
  space_game.GameRun();
  space_game.GameTerminate();

  return 0;
}