#include "SpaceHeader.hpp"

void SpaceGame::RenderMenu() {
  SDL_SetRenderDrawColor(game_renderer.renderer, 0, 0, 0, 255);
  SDL_RenderClear(game_renderer.renderer);
  RenderBackground();
  RenderPlayButton();
  SDL_RenderPresent(game_renderer.renderer);
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
  SDL_SetRenderDrawColor(game_renderer.renderer, 0, 0, 0, 255);
  SDL_RenderClear(game_renderer.renderer);
  SDL_RenderPresent(game_renderer.renderer);
}