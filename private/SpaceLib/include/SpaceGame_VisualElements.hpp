#pragma once

#include "SpaceGame_DataStructures.hpp"
#include "SpaceGame_Macros.hpp"
#include "SpaceGame_Renderer.hpp"

class Background {
  private:
    BackgroundStar background_stars[BACKGROUND_STAR_AMOUNT];
    SDL_Texture* star_texture;
  public:
    //Background();
    void SetStarTexture(SDL_Texture* texture);
    void CreateBackground();
    void UpdateAndRenderBackground(AppState game_state, Renderer game_renderer);
};

class Title {
  protected:
    SDL_Texture* title_texture;
    SDL_FRect title_rect;
  public:
    void CreateTitle(float pos_x, float pos_y, float width, float height);
    void SetTitleTexture(SDL_Texture* texture);
    void UpdateTitleLocation(float pos_x, float pos_y);
    void RenderTitle(SDL_Renderer* renderer);
};

class GameTitle : public Title {
  private:
    double color_shift;
  public:
    void CreateTitle(float pos_x, float pos_y, float width, float height);
    void UpdateTitleColor(double delta_time);
    void Render(SDL_Renderer* renderer);
};