#include "SpaceHeader.hpp"

HomeButton::HomeButton(float center_x, float center_y, SDL_Texture* texture) {
  this->button_rect = {
    center_x - (SCREEN_BUTTON_SIZE / 2.0f),
    center_y - (SCREEN_BUTTON_SIZE / 2.0f),
    SCREEN_BUTTON_SIZE,
    SCREEN_BUTTON_SIZE
  };
  this->button_texture = texture;
  this->is_hovered = false;
  this->is_pressed = false;
}

void HomeButton::CheckButtonState(Input input) {
  float roof_slope_const = (input.mouse.pos_y - button_rect.y) * 4.0f / 5.0f;
  bool roof_hovered_y = input.mouse.pos_y >= button_rect.y && input.mouse.pos_y <= button_rect.y + (SCREEN_BUTTON_SIZE * 2.0 / 5.0f);
  bool roof_hovered_x_01 = input.mouse.pos_x >= button_rect.x + roof_slope_const;
  bool roof_hovered_x_02 = input.mouse.pos_x <= button_rect.x + SCREEN_BUTTON_SIZE - roof_slope_const;
  bool roof_hovered = roof_hovered_y && roof_hovered_x_01 && roof_hovered_x_02;
  bool base_hovered_x = input.mouse.pos_x >= button_rect.x + SCREEN_BUTTON_SIZE / 10.0f && input.mouse.pos_x <= button_rect.x + SCREEN_BUTTON_SIZE - (SCREEN_BUTTON_SIZE / 10.0f);
  bool base_hovered_y = input.mouse.pos_y >= button_rect.y + (SCREEN_BUTTON_SIZE * 2.0f / 5.0f) && input.mouse.pos_y <= button_rect.y + SCREEN_BUTTON_SIZE;
  bool base_hovered = base_hovered_x && base_hovered_y;
  if ((roof_hovered || base_hovered) || input.input_keys[BUTTON_ESCAPE].is_down) {
    is_hovered = true;
    if (ButtonPressed(MOUSE_BUTTON_LEFT) || ButtonReleased(BUTTON_ESCAPE)) {
      is_pressed = true;
    }
  }
  else {
    is_hovered = false;
    is_pressed = false;
  }
}

void HomeButton::Render(SDL_Renderer* renderer) {
  if (is_hovered) {
    SDL_SetTextureColorMod(button_texture, 201, 49, 33);
  }
  else {
    SDL_SetTextureColorMod(button_texture, 255, 255, 255);
  }
  SDL_RenderTexture(renderer, button_texture, NULL, &button_rect);
}

bool HomeButton::Pressed() {
  return is_pressed;
}