#include "SpaceHeader.hpp"
/*
PauseMenu::PauseMenu() :
  play_button(Utils::window_width / 4.0f, (Utils::window_height / 2.0f)),
  home_button((Utils::window_width / 4.0f) * 3.0f, (Utils::window_height / 2.0f))
{}
*/

void PauseMenu::ResetButtons() {
  play_button.ResetButtonState();
  home_button.ResetButtonState();
}

void PauseMenu::CreateMenu() {
  play_button.CreateButton(Utils::window_width / 4.0f, (Utils::window_height / 2.0f));
  home_button.CreateButton((Utils::window_width / 4.0f) * 3.0f, (Utils::window_height / 2.0f));
}

void PauseMenu::UpdateMenu() {
  play_button.UpdateButtonLocation(Utils::window_width / 4.0f, (Utils::window_height / 2.0f));
  home_button.UpdateButtonLocation((Utils::window_width / 4.0f) * 3.0f, (Utils::window_height / 2.0f));
}

void PauseMenu::RenderMenu(SDL_Renderer* renderer) {
  play_button.Render(renderer);
  home_button.Render(renderer);
}