#include "SpaceHeader.hpp"

GameTitle::GameTitle(float center_x, float center_y, SDL_Texture* texture) {
  this->title_rect = {
    center_x - (TITLE_WIDTH / 2.0f),
    center_y - (TITLE_HEIGHT / 2.0f),
    TITLE_WIDTH,
    TITLE_HEIGHT
  };
  this->title_texture = texture;
  this->color_shift = 0.0f;
}

void GameTitle::UpdateTitle(double delta_time) {
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