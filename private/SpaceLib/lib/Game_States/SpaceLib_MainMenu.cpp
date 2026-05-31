#include "SpaceGame_GameScreens.hpp"
#include "SpaceGame_Utils.hpp"

#ifndef TITLE_WIDTH
  #define TITLE_WIDTH 580.0f
#endif

#ifndef TITLE_HEIGHT
  #define TITLE_HEIGHT TITLE_WIDTH * 57.0f / 87.0f
#endif

void MainMenu::CreateMenu() {
  play_button.CreateButton(Utils::window_width / 2.0f, (Utils::window_height / 4.0f) * 3.0f);
  title.CreateTitle(Utils::window_width / 2.0f, Utils::window_height / 4.0f, TITLE_WIDTH, TITLE_HEIGHT);
}

void MainMenu::ResetButtons() {
  play_button.ResetButtonState();
}

void MainMenu::UpdateMenu(AppState game_state) {
  title.UpdateTitleLocation(Utils::window_width / 2.0f, Utils::window_height / 4.0f);
  title.UpdateTitleColor(game_state.delta_time);
  play_button.UpdateButtonLocation(Utils::window_width / 2.0f, (Utils::window_height / 4.0f) * 3.0f);
}

void MainMenu::RenderMenu(SDL_Renderer* renderer) {
  title.Render(renderer);
  play_button.Render(renderer);
}