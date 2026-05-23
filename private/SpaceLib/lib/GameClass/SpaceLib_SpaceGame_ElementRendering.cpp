#include "SpaceHeader.hpp"

void SpaceGame::CreateBackground() {
 for(int i = 0; i < BACKGROUND_STAR_AMOUNT; i++) {
  background_stars[i].star_location.x = (SDL_randf() * (float)game_state.display_data.display_mode->w);
  background_stars[i].star_location.y = (SDL_randf() * (float)game_state.display_data.display_mode->h);
  background_stars[i].star_speed = MIN_BACKGROUND_STAR_SPEED + (SDL_randf() * (MAX_BACKGROUND_STAR_SPEED - MIN_BACKGROUND_STAR_SPEED));
 }
}

void SpaceGame::RenderBackground() {
  int window_x, window_y;
  int brightness_int;
  float star_size;
  bool star_is_outside_x, star_is_outside_y;
  SDL_GetWindowPosition(game_renderer.window, &window_x, &window_y);
  for (int i = 0; i < BACKGROUND_STAR_AMOUNT; i++) {
    //Update star location
    background_stars[i].star_location.x += background_stars[i].star_speed * (float)game_state.delta_time;
    background_stars[i].star_location.y += background_stars[i].star_speed * (float)game_state.delta_time;
    //Respawn star if it goes off-display
    star_is_outside_x = background_stars[i].star_location.x > (game_state.display_data.display_mode->w);
    star_is_outside_y = background_stars[i].star_location.y > (game_state.display_data.display_mode->h);
    if (star_is_outside_x || star_is_outside_y) {
      if (SDL_rand(2)) {
        background_stars[i].star_location.x = (SDL_randf() * game_state.display_data.display_mode->w);
        background_stars[i].star_location.y = -(float)window_y;
      }
      else {
        background_stars[i].star_location.x = -(float)window_x;
        background_stars[i].star_location.y = (SDL_randf() * game_state.display_data.display_mode->h);
      }
    }
    //Calculate star brightness based on its speed
    background_stars[i].star_brightness = InvLerpF(background_stars[i].star_speed, MIN_BACKGROUND_STAR_SPEED, MAX_BACKGROUND_STAR_SPEED);
    background_stars[i].star_brightness = ClampF(background_stars[i].star_brightness, MIN_BACKGROUND_STAR_BRIGHTNESS, 1.0);
    brightness_int = (int)(background_stars[i].star_brightness * 255.0);

    //Draw star to screen
    if (brightness_int > 200) {
      star_size = 5.0f + (brightness_int - 200.0f) / 5.0f; //Size the star based on its brightness, with a minimum size of 5.0f
      SDL_FRect dest_rect = {background_stars[i].star_location.x - star_size/2, background_stars[i].star_location.y - star_size/2, star_size, star_size };
      SDL_RenderTexture(game_renderer.renderer, game_renderer.default_star_texture, NULL, &dest_rect);
      continue; //Skip drawing the star as a point if it's bright enough to be drawn as a texture
    }
    SDL_SetRenderDrawColor(game_renderer.renderer, brightness_int, brightness_int, brightness_int, 255);
    SDL_RenderPoint(game_renderer.renderer, background_stars[i].star_location.x, background_stars[i].star_location.y);
  }
}

void SpaceGame::RenderPlayButton() {
  float play_button_x = game_renderer.window_width / 2.0f - PLAY_BUTTON_SIZE / 2.0f;
  float play_button_y = (game_renderer.window_height / 4.0f) * 3.0f - PLAY_BUTTON_SIZE / 2.0f;
  SDL_FRect play_button_rect = {
    play_button_x,
    play_button_y,
    PLAY_BUTTON_SIZE,
    PLAY_BUTTON_SIZE
  };

  float slope_ratio = (input.mouse.pos_x - play_button_x) / 2.0f;
  bool mouse_x_hovered = input.mouse.pos_x >= play_button_x && input.mouse.pos_x <= (play_button_x + PLAY_BUTTON_SIZE);
  bool mouse_y_hovered = input.mouse.pos_y >= play_button_y + slope_ratio && input.mouse.pos_y <= (play_button_y + PLAY_BUTTON_SIZE) - slope_ratio;
  if ((mouse_x_hovered && mouse_y_hovered) || input.input_keys[BUTTON_RETURN].is_down) {
    SDL_SetTextureColorMod(game_renderer.triangle_texture, 56, 178, 94);
    SDL_RenderTexture(game_renderer.renderer, game_renderer.triangle_texture, NULL, &play_button_rect);
    if (ButtonPressed(MOUSE_BUTTON_LEFT)) {
      game_state.current_state = STATE_PLAYING;
    }
  }
  else {
    SDL_SetTextureColorMod(game_renderer.triangle_texture, 255, 255, 255);
    SDL_RenderTexture(game_renderer.renderer, game_renderer.triangle_texture, NULL, &play_button_rect);
  }
}