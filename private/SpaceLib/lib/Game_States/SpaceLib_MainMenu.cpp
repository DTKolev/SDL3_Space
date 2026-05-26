#include "SpaceHeader.hpp"

MainMenu::MainMenu(Renderer game_renderer) :
  play_button(game_renderer.window_width / 2.0f, (game_renderer.window_height / 4.0f) * 3.0f, game_renderer.play_button_texture),
  title(game_renderer.window_width / 2.0f, game_renderer.window_height / 4.0f, game_renderer.title_texture)
{}

void MainMenu::UpdateMenu(AppState game_state, Input input) {
  play_button.CheckButtonState(input);
  title.UpdateTitle(game_state.delta_time);
}

void MainMenu::RenderMenu(SDL_Renderer* renderer) {
  title.Render(renderer);
  play_button.Render(renderer);
}