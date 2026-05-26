#include "SpaceHeader.hpp"

DeathScreen::DeathScreen(Renderer game_renderer) :
  play_button(game_renderer.window_width / 2.0f, (game_renderer.window_height / 2.0f), game_renderer.play_button_texture),
  home_button(game_renderer.window_width / 2.0f, (game_renderer.window_height / 4.0f) * 3.0f, game_renderer.home_button_texture)
{}

void DeathScreen::UpdateMenu(Input input) {
  play_button.CheckButtonState(input);
  home_button.CheckButtonState(input);
}

void DeathScreen::RenderMenu(SDL_Renderer* renderer) {
  play_button.Render(renderer);
  home_button.Render(renderer);
}