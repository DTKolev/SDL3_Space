#include "SpaceHeader.hpp"

void GameTitle::CreateTitle(float pos_x, float pos_y, float width, float height) {
  this->title_rect = {
    .x = pos_x - (width / 2.0f),
    .y = pos_y - (height / 2.0f),
    .w = width,
    .h = height
  };
  this->color_shift = 0.0;
}

void GameTitle::UpdateTitleColor(double delta_time) {
  color_shift += delta_time;
}

void GameTitle::Render(SDL_Renderer* renderer) {
  int red, grreen, blue;
  red = (int)((0.5 + 0.5 * SDL_sin(color_shift)) * 255);
  grreen = (int)((0.5 + 0.5 * SDL_sin(color_shift + SDL_PI_D * 2.0f / 3.0f)) * 255);
  blue = (int)((0.5 + 0.5 * SDL_sin(color_shift + SDL_PI_D * 4.0f / 3.0f)) * 255);
  SDL_SetTextureColorMod(title_texture, red, grreen, blue);
  SDL_RenderTexture(renderer, title_texture, NULL, &title_rect);
}