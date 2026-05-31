#include <SDL3/SDL.h>

#include "SpaceGame_ScoreCounter.hpp"

#ifndef DIGIT_WIDTH
  #define DIGIT_WIDTH 50.0f
#endif

#ifndef DIGIT_HEIGHT
  #define DIGIT_HEIGHT DIGIT_WIDTH * 18.0f / 10.0f
#endif

#ifndef DIGIT_SPACING
  #define DIGIT_SPACING DIGIT_WIDTH / 5.0f
#endif

void ScoreCounter::CreateCounter(float pos_x, float pos_y) {
  counter_location = {
    .x = pos_x,
    .y = pos_y
  };
}

void ScoreCounter::IncrementScore(PlanetManager planet_manager) {
  if (planet_manager.asteroid_hit && !planet_manager.asteroid_hit_planet) score++;
}

void ScoreCounter::SetDigitTextures(Renderer game_renderer) {
  for (int i = 0; i <= 9; i++) {
    digit_textures[i] = game_renderer.PreRenderDigitTexture(i);
  }
}

void ScoreCounter::RenderScore(SDL_Renderer* renderer) {
  int digits[3] = {
    (score / 100) % 10,
    (score / 10) % 10,
    score % 10
  };
  SDL_FRect digit_rects[3] = {
    {counter_location.x, counter_location.y, DIGIT_WIDTH, DIGIT_HEIGHT},
    {counter_location.x + DIGIT_WIDTH + DIGIT_SPACING, counter_location.y, DIGIT_WIDTH, DIGIT_HEIGHT},
    {counter_location.x + 2.0f * (DIGIT_WIDTH + DIGIT_SPACING), counter_location.y, DIGIT_WIDTH, DIGIT_HEIGHT}
  };

  for (int i = 0; i < 3; i++) {
    SDL_RenderTexture(renderer, digit_textures[digits[i]], NULL, &digit_rects[i]);
  }
}

void ScoreCounter::ResetScore() {
  score = 0;
}

void ScoreCounter::DestroyDigitTextures() {
  for (int i = 0; i <= 9; i++) {
    SDL_DestroyTexture(digit_textures[i]);
  }
}