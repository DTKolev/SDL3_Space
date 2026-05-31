#include <SDL3/SDL.h>

#include "SpaceGame_VisualElements.hpp"
#include "SpaceGame_Utils.hpp"

#ifndef BACKGROUND_STAR_AMOUNT
  #define BACKGROUND_STAR_AMOUNT 1000
#endif

#ifndef MIN_BACKGROUND_STAR_SPEED
  #define MIN_BACKGROUND_STAR_SPEED 15.0f
#endif

#ifndef MAX_BACKGROUND_STAR_SPEED
  #define MAX_BACKGROUND_STAR_SPEED 30.0f
#endif

#ifndef MIN_BACKGROUND_STAR_BRIGHTNESS
  #define MIN_BACKGROUND_STAR_BRIGHTNESS 0.2f
#endif

void Background::SetStarTexture(SDL_Texture* texture) {
  star_texture = texture;
}

void Background::CreateBackground() {
  float brightness_f;
  for(int i = 0; i < BACKGROUND_STAR_AMOUNT; i++) {
    background_stars[i].star_location.x = (SDL_randf() * (float)Utils::display_data.display_mode->w);
    background_stars[i].star_location.y = (SDL_randf() * (float)Utils::display_data.display_mode->h);
    background_stars[i].star_speed = MIN_BACKGROUND_STAR_SPEED + (SDL_randf() * (MAX_BACKGROUND_STAR_SPEED - MIN_BACKGROUND_STAR_SPEED));

    brightness_f = Utils::InvLerpF(background_stars[i].star_speed, MIN_BACKGROUND_STAR_SPEED, MAX_BACKGROUND_STAR_SPEED);
    brightness_f = Utils::ClampF(brightness_f, MIN_BACKGROUND_STAR_BRIGHTNESS, 1.0);
    background_stars[i].star_brightness = (int)(brightness_f * 255.0);
  }
}

void Background::UpdateAndRenderBackground(AppState game_state, Renderer game_renderer) {
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
    star_is_outside_x = background_stars[i].star_location.x > (Utils::display_data.display_mode->w);
    star_is_outside_y = background_stars[i].star_location.y > (Utils::display_data.display_mode->h);
    if (star_is_outside_x || star_is_outside_y) {
      if (SDL_rand(2)) {
        background_stars[i].star_location.x = (SDL_randf() * Utils::display_data.display_mode->w);
        background_stars[i].star_location.y = -(float)window_y;
      }
      else {
        background_stars[i].star_location.x = -(float)window_x;
        background_stars[i].star_location.y = (SDL_randf() * Utils::display_data.display_mode->h);
      }
    }

    //Draw star to screen
    if (background_stars[i].star_brightness > 200) {
      star_size = 5.0f + (background_stars[i].star_brightness - 200.0f) / 5.0f; //Size the star based on its brightness, with a minimum size of 5.0f
      SDL_FRect dest_rect = {background_stars[i].star_location.x - star_size/2, background_stars[i].star_location.y - star_size/2, star_size, star_size };
      SDL_RenderTexture(game_renderer.renderer, star_texture, NULL, &dest_rect);
      continue; //Skip drawing the star as a point if it's bright enough to be drawn as a texture
    }
    SDL_SetRenderDrawColor(
      game_renderer.renderer, 
      background_stars[i].star_brightness, background_stars[i].star_brightness, background_stars[i].star_brightness, 255
    );
    SDL_RenderPoint(game_renderer.renderer, background_stars[i].star_location.x, background_stars[i].star_location.y);
  }
}