#include "SpaceHeader.hpp"

void SpaceGame::HandleMenu() {
  if (ButtonReleased(BUTTON_RETURN) || input.play_button_pressed) {
    for (int i = 1; i < PLANET_AMOUNT; i++) {
      SetRandomProperties(&planets[i]);
      game_renderer.PreRenderPlanetTexture(&planets[i]);
    }
    game_renderer.grid_scale = 1.0f;
    game_renderer.CalculateOriginOffset();
    game_state.current_state = STATE_PLAYING;
    input.play_button_pressed = false;
  }
  else if (ButtonReleased(BUTTON_ESCAPE)) game_state.current_state = STATE_EXIT;
}

void SpaceGame::HandlePlaying() {
  if (ButtonReleased(BUTTON_P) || ButtonReleased(BUTTON_ESCAPE)) game_state.current_state = STATE_PAUSE;
}

void SpaceGame::HandlePause() {
  if (ButtonReleased(BUTTON_P) || ButtonReleased(BUTTON_RETURN) || input.play_button_pressed) {
    game_state.current_state = STATE_PLAYING;
    input.play_button_pressed = false;
  }
  else if (ButtonReleased(BUTTON_ESCAPE) || ButtonReleased(BUTTON_Q) || input.home_button_pressed) {
    game_state.current_state = STATE_MENU;
    input.home_button_pressed = false;
  }
}