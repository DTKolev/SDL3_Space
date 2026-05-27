#include "SpaceHeader.hpp"

void ScreenButton::SetButtonTexture(SDL_Texture* texture) {
  this->button_texture = texture;
}

void ScreenButton::CreateButton(float x, float y) {
  this->button_rect = {
    x - (SCREEN_BUTTON_SIZE / 2.0f),
    y - (SCREEN_BUTTON_SIZE / 2.0f),
    SCREEN_BUTTON_SIZE,
    SCREEN_BUTTON_SIZE
  };
  this->is_hovered = false;
  this->is_pressed = false;
}

void ScreenButton::UpdateButtonLocation(float x, float y) {
  this->button_rect.x = x - (SCREEN_BUTTON_SIZE / 2.0f);
  this->button_rect.y = y - (SCREEN_BUTTON_SIZE / 2.0f);
}

void ScreenButton::ResetButtonState() {
  this->is_pressed = false;
}

bool ScreenButton::Pressed() {
  return this->is_pressed;
}