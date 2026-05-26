#include "SpaceHeader.hpp"

MainMenu::MainMenu() :
  play_button(utils.window_width / 2.0f, (utils.window_height / 4.0f) * 3.0f),
  title(utils.window_width / 2.0f, utils.window_height / 4.0f)
{}

void MainMenu::ResetButtons() {
  play_button.ResetButtonState();
}

void MainMenu::UpdateMenu(AppState game_state, Input input) {
  play_button.CheckButtonState(input);
  title.UpdateTitle(game_state.delta_time);
}

void MainMenu::RenderMenu(SDL_Renderer* renderer) {
  title.Render(renderer);
  play_button.Render(renderer);
}