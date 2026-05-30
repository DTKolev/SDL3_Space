#include "SpaceHeader.hpp"

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