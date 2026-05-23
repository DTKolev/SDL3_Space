#include "SpaceHeader.hpp"

void SpaceGame::RenderMenu() {

}

void SpaceGame::RenderPlaying() {
  SDL_SetRenderDrawColor(game_renderer.renderer, 0, 0, 0, 0);
  SDL_RenderClear(game_renderer.renderer);
  UpdatePlanetOrbits();
  RenderBackground();
  RenderPlanets();
  SDL_RenderPresent(game_renderer.renderer);
  
}

void SpaceGame::RenderPause() {

}