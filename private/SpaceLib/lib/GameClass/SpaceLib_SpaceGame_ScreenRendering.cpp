#include "SpaceHeader.hpp"

void SpaceGame::RenderMenu() {
  RenderTitle();
  RenderPlayButton(game_renderer.window_width / 2.0f, (game_renderer.window_height / 4.0f) * 3.0f);
}

void SpaceGame::RenderPlaying() {
  UpdatePlanetOrbits();
  RenderPlanets();  
}

void SpaceGame::RenderPause() {
  RenderPlayButton(game_renderer.window_width / 4.0f, (game_renderer.window_height / 2.0f));
  RenderHomeButton((game_renderer.window_width / 4.0f) * 3.0f, (game_renderer.window_height / 2.0f));
}