#include "SpaceGame_GameScreens.hpp"
#include "SpaceGame_Utils.hpp"

#ifndef PAUSE_TITLE_WIDTH
  #define PAUSE_TITLE_WIDTH 580.0f
#endif

#ifndef PAUSE_TITLE_HEIGHT
  #define PAUSE_TITLE_HEIGHT PAUSE_TITLE_WIDTH * 27.0f / 87.0f
#endif

void PauseMenu::ResetButtons() {
  play_button.ResetButtonState();
  home_button.ResetButtonState();
}

void PauseMenu::CreateMenu() {
  pause_title.CreateTitle(Utils::window_width / 2.0f, Utils::window_height / 4.0f, PAUSE_TITLE_WIDTH, PAUSE_TITLE_HEIGHT);
  play_button.CreateButton(Utils::window_width / 4.0f, (Utils::window_height / 2.0f));
  home_button.CreateButton((Utils::window_width / 4.0f) * 3.0f, (Utils::window_height / 2.0f));
}

void PauseMenu::UpdateMenu() {
  pause_title.UpdateTitleLocation(Utils::window_width / 2.0f, Utils::window_height / 4.0f);
  play_button.UpdateButtonLocation(Utils::window_width / 4.0f, (Utils::window_height / 2.0f));
  home_button.UpdateButtonLocation((Utils::window_width / 4.0f) * 3.0f, (Utils::window_height / 2.0f));
}

void PauseMenu::RenderMenu(SDL_Renderer* renderer) {
  pause_title.RenderTitle(renderer);
  play_button.Render(renderer);
  home_button.Render(renderer);
}