#pragma once

#include "SpaceGame_DataStructures.hpp"

class Renderer {
  private:
    void PrepareTextureForPreRendering(SDL_Texture** texture, int width, int height);
  public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* default_star_texture;
    SDL_Texture* play_button_texture;
    SDL_Texture* home_button_texture;
    SDL_Texture* title_texture;
    SDL_Texture* pause_texture;
    SDL_Texture* death_texture;

    //Renderer();
    void CreateWindowAndRenderer();
    void PreRenderPlanetTexture(Planet* planet);
    void RenderPlanet(Planet planet);
    void PreRenderDefaultStarTexture();
    void PreRenderPlayButtonTexture();
    void PreRenderHomeButtonTexture();
    void PreRenderTitleTexture();
    void PreRenderPauseTexture();
    void PreRenderDeathTexture();
};