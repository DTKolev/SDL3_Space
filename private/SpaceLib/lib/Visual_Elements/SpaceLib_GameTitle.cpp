#include "SpaceHeader.hpp"

void GameTitle::CreateTitle(float x, float y) {
  this->title_rect = {
    x - (TITLE_WIDTH / 2.0f),
    y - (TITLE_HEIGHT / 2.0f),
    TITLE_WIDTH,
    TITLE_HEIGHT
  };
  this->color_shift = 0.0f;
}

void GameTitle::SetTitleTexture(SDL_Texture* texture) {
  title_texture = texture;
}

void GameTitle::UpdateTitle(float x, float y, double delta_time) {
  title_rect.x = x - (TITLE_WIDTH / 2.0f);
  title_rect.y = y - (TITLE_HEIGHT / 2.0f);
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