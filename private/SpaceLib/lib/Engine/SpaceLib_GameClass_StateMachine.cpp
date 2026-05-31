#include "SpaceGame_Engine.hpp"

void SpaceGame::HandleMenu() {
  if (ButtonReleased(BUTTON_RETURN) || main_menu.play_button.Pressed()) {
    game_state.current_state = STATE_PLAYING;
    game_screen.CreateGameScreen(&game_state, game_renderer);
    game_screen.score_counter.ResetScore();
  }
  if (ButtonReleased(BUTTON_ESCAPE)) game_state.current_state = STATE_EXIT;
}

void SpaceGame::HandlePlaying() {
  if (ButtonReleased(BUTTON_Q) || ButtonReleased(BUTTON_P) || ButtonReleased(BUTTON_ESCAPE)) {
    game_state.current_state = STATE_PAUSE;
    UpdateScreenButtonsStates();
  }
  if (game_screen.planet_manager.asteroid_hit_planet) {
    game_state.current_state = STATE_DEATH_SCREEN;
    UpdateScreenButtonsStates();
  }
}

void SpaceGame::HandlePause() {
  if (ButtonReleased(BUTTON_RETURN) || pause_menu.play_button.Pressed()) game_state.current_state = STATE_PLAYING;
  if (ButtonReleased(BUTTON_ESCAPE) || pause_menu.home_button.Pressed()) {
    game_state.current_state = STATE_MENU;
    UpdateScreenButtonsStates();
  }
}

void SpaceGame::HandleDeathScreen() {
  if (ButtonReleased(BUTTON_RETURN) || death_screen.play_button.Pressed()) { 
    game_screen.CreateGameScreen(&game_state, game_renderer);
    game_state.current_state = STATE_PLAYING;
    game_screen.score_counter.ResetScore();
  }
  if (ButtonReleased(BUTTON_ESCAPE) || death_screen.home_button.Pressed()) game_state.current_state = STATE_MENU;
}