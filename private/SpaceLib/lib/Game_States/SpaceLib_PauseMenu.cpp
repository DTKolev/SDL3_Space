#include "SpaceHeader.hpp"

PauseMenu::PauseMenu() :
  play_button(utils.window_width / 4.0f, (utils.window_height / 2.0f)),
  home_button((utils.window_width / 4.0f) * 3.0f, (utils.window_height / 2.0f))
{}

void PauseMenu::ResetButtons() {
  play_button.ResetButtonState();
  home_button.ResetButtonState();
}

void PauseMenu::UpdateMenu(Input input) {
  play_button.CheckButtonState(input);
  home_button.CheckButtonState(input);
}

void PauseMenu::RenderMenu(SDL_Renderer* renderer) {
  play_button.Render(renderer);
  home_button.Render(renderer);
}