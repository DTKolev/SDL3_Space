#include "SpaceHeader.hpp"

PlayButton::PlayButton(float center_x, float center_y) {
  this->button_rect = {
    center_x - (SCREEN_BUTTON_SIZE / 2.0f),
    center_y - (SCREEN_BUTTON_SIZE / 2.0f),
    SCREEN_BUTTON_SIZE,
    SCREEN_BUTTON_SIZE
  };
  this->is_hovered = false;
  this->is_pressed = false;
}

void PlayButton::SetButtonTexture(SDL_Texture* texture) {
  button_texture = texture;
}

void PlayButton::CheckButtonState(Input input) {
  float slope_const = (input.mouse.pos_x - button_rect.x) / 2.0f;
  bool mouse_x_hovered = input.mouse.pos_x >= button_rect.x && input.mouse.pos_x <= (button_rect.x + SCREEN_BUTTON_SIZE);
  bool mouse_y_hovered = input.mouse.pos_y >= button_rect.y + slope_const && input.mouse.pos_y <= (button_rect.y + SCREEN_BUTTON_SIZE) - slope_const;
  if ((mouse_x_hovered && mouse_y_hovered) || input.input_keys[BUTTON_RETURN].is_down) {
    is_hovered = true;
    if (ButtonPressed(MOUSE_BUTTON_LEFT) || ButtonReleased(BUTTON_RETURN)) {
      is_pressed = true;
    }
  }
  else {
    is_hovered = false;
  }
}

void PlayButton::ResetButtonState() {
  is_pressed = false;
}

void PlayButton::Render(SDL_Renderer* renderer) {
  if (is_hovered) {
    SDL_SetTextureColorMod(button_texture, 56, 178, 94);
  }
  else {
    SDL_SetTextureColorMod(button_texture, 255, 255, 255);
  }
  SDL_RenderTexture(renderer, button_texture, NULL, &button_rect);
}

bool PlayButton::Pressed() {
  return is_pressed;
}