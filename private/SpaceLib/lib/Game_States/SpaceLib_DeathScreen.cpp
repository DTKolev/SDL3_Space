#include "SpaceGame_GameScreens.hpp"
#include "SpaceGame_Utils.hpp"

#ifndef DEATH_TITLE_WIDTH
  #define DEATH_TITLE_WIDTH 860.0f
#endif
#ifndef DEATH_TITLE_HEIGHT
  #define DEATH_TITLE_HEIGHT DEATH_TITLE_WIDTH * 27.0f / 129.0f
#endif

void DeathScreen::CreateMenu() {
  death_title.CreateTitle(Utils::window_width / 2.0f, Utils::window_height / 4.0f, DEATH_TITLE_WIDTH, DEATH_TITLE_HEIGHT);
  play_button.CreateButton(Utils::window_width / 2.0f, (Utils::window_height / 2.0f));
  home_button.CreateButton(Utils::window_width / 2.0f, (Utils::window_height / 4.0f) * 3.0f);
}

void DeathScreen::ResetButtons() {
  play_button.ResetButtonState();
  home_button.ResetButtonState();
}

void DeathScreen::UpdateMenu() {
  death_title.UpdateTitleLocation(Utils::window_width / 2.0f, Utils::window_height / 4.0f);
  play_button.UpdateButtonLocation(Utils::window_width / 2.0f, (Utils::window_height / 2.0f));
  home_button.UpdateButtonLocation(Utils::window_width / 2.0f, (Utils::window_height / 4.0f) * 3.0f);
}

void DeathScreen::RenderMenu(SDL_Renderer* renderer) {
  death_title.RenderTitle(renderer);
  play_button.Render(renderer);
  home_button.Render(renderer);
}