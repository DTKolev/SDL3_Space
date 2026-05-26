#include "SpaceHeader.hpp"

DeathScreen::DeathScreen() :
  play_button(Utils::window_width / 2.0f, (Utils::window_height / 2.0f)),
  home_button(Utils::window_width / 2.0f, (Utils::window_height / 4.0f) * 3.0f)
{}

void DeathScreen::ResetButtons() {
  play_button.ResetButtonState();
  home_button.ResetButtonState();
}

void DeathScreen::UpdateMenu(Input input) {
  play_button.CheckButtonState(input);
  home_button.CheckButtonState(input);
}

void DeathScreen::RenderMenu(SDL_Renderer* renderer) {
  play_button.Render(renderer);
  home_button.Render(renderer);
}