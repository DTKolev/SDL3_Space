#include "SpaceHeader.hpp"

void SpaceGame::HandleMenu() {
  if (ButtonPressed(BUTTON_RETURN)) game_state.current_state = STATE_PLAYING;
  else if (ButtonPressed(BUTTON_ESCAPE)) game_state.current_state = STATE_EXIT;
}

void SpaceGame::HandlePlaying() {
  if (ButtonPressed(BUTTON_P) || ButtonPressed(BUTTON_ESCAPE)) game_state.current_state = STATE_PAUSE;
}

void SpaceGame::HandlePause() {
  if (ButtonPressed(BUTTON_P) || ButtonPressed(BUTTON_RETURN)) game_state.current_state = STATE_PLAYING;
  else if (ButtonPressed(BUTTON_ESCAPE) || ButtonPressed(BUTTON_Q)) game_state.current_state = STATE_MENU;
}