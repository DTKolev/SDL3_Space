#include "SpaceHeader.hpp"

void SpaceGame::HandleMenu() {
  if (ButtonReleased(BUTTON_RETURN)) game_state.current_state = STATE_PLAYING;
  else if (ButtonReleased(BUTTON_ESCAPE)) game_state.current_state = STATE_EXIT;
}

void SpaceGame::HandlePlaying() {
  if (ButtonReleased(BUTTON_P) || ButtonReleased(BUTTON_ESCAPE)) game_state.current_state = STATE_PAUSE;
}

void SpaceGame::HandlePause() {
  if (ButtonReleased(BUTTON_P) || ButtonReleased(BUTTON_RETURN)) game_state.current_state = STATE_PLAYING;
  else if (ButtonReleased(BUTTON_ESCAPE) || ButtonReleased(BUTTON_Q)) game_state.current_state = STATE_MENU;
}