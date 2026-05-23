#include "SpaceHeader.hpp"

void SpaceGame::RenderMenu() {
  float play_button_x = game_renderer.window_width / 2.0f - PLAY_BUTTON_SIZE / 2.0f;
  float play_button_y = (game_renderer.window_height / 4.0f) * 3.0f - PLAY_BUTTON_SIZE / 2.0f;

  SDL_SetRenderDrawColor(game_renderer.renderer, 0, 0, 0, 255);
  SDL_RenderClear(game_renderer.renderer);
  SDL_FRect play_button_rect = {
    play_button_x,
    play_button_y,
    PLAY_BUTTON_SIZE,
    PLAY_BUTTON_SIZE
  };
  SDL_RenderTexture(game_renderer.renderer, game_renderer.triangle_texture, NULL, &play_button_rect);
  SDL_RenderPresent(game_renderer.renderer);

  bool play_button_is_hovered_x = input.mouse.pos_x >= play_button_x && input.mouse.pos_x <= (play_button_x + PLAY_BUTTON_SIZE);
  bool play_button_is_hovered_y = input.mouse.pos_y >= play_button_y && input.mouse.pos_y <= (play_button_y + PLAY_BUTTON_SIZE);
  if (ButtonPressed(MOUSE_BUTTON_LEFT) && play_button_is_hovered_x && play_button_is_hovered_y) {
    game_state.current_state = STATE_PLAYING;
  }
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