#include <SDL3/SDL.h>

#include "SpaceGame_VisualElements.hpp"
#include "SpaceGame_DataStructures.hpp"

void Title::CreateTitle(float pos_x, float pos_y, float width, float height) {
  this->title_rect = {
    .x = pos_x - width / 2.0f,
    .y = pos_y - height / 2.0f,
    .w = width,
    .h = height
  };
}

void Title::SetTitleTexture(SDL_Texture* texture) {
 this->title_texture = texture;
}

void Title::UpdateTitleLocation(float pos_x, float pos_y) {
  this->title_rect.x = pos_x - (title_rect.w / 2.0f);
  this->title_rect.y = pos_y - (title_rect.h / 2.0f);
}

void Title::RenderTitle(SDL_Renderer* renderer) {
  SDL_RenderTexture(renderer, title_texture, NULL, &title_rect);
}