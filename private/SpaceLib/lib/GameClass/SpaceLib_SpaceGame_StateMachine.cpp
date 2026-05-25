#include "SpaceHeader.hpp"

void SpaceGame::HandleMenu() {
  if (ButtonReleased(BUTTON_RETURN) || input.play_button_pressed) {
    ResetGame();
    input.play_button_pressed = false;
    game_state.current_state = STATE_PLAYING;
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

void SpaceGame::HandleDeathScreen() {
  if (ButtonReleased(BUTTON_RETURN) || input.play_button_pressed) {
    ResetGame();
    input.play_button_pressed = false;
    game_state.current_state = STATE_PLAYING;
  }
  else if (ButtonReleased(BUTTON_ESCAPE) || ButtonReleased(BUTTON_Q) || input.home_button_pressed) {
    game_state.current_state = STATE_MENU;
    input.home_button_pressed = false;
  }
}