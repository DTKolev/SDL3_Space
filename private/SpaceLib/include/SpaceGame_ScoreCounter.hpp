#pragma once

#include "SpaceGame_DataStructures.hpp"
#include "SpaceGame_Renderer.hpp"
#include "SpaceGame_PlanetManager.hpp"

class ScoreCounter {
  private:
    int score;
    SDL_Texture* digit_textures[10];
    SDL_FPoint counter_location;
  public:
    void CreateCounter(float pos_x, float pos_y);
    void IncrementScore(PlanetManager planet_manager);
    void SetDigitTextures(Renderer game_renderer);
    void RenderScore(SDL_Renderer* renderer);
    void ResetScore();
};