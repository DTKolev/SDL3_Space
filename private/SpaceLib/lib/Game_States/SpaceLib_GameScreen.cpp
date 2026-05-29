#include "SpaceHeader.hpp"

void GameScreen::CreateGameScreen(AppState* game_state, Renderer game_renderer) {
  planet_manager.ResetGame(game_state, game_renderer);
}

void GameScreen::UpdateGameScreen(AppState* game_state, Input input) {
  planet_manager.SpawnAsteroid(game_state);
  planet_manager.UpdateAsteroid(game_state);
  planet_manager.UpdatePlanetOrbits(*game_state);
  planet_manager.ManualPlanetMove(*game_state, input);
  planet_manager.CheckAsteroidCollision();
}

void GameScreen::RenderGameScreen(Renderer game_renderer) {
  planet_manager.RenderAsteroid(game_renderer.renderer);
  planet_manager.RenderPlanets(game_renderer);
}