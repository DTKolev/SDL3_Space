#pragma once

#include "SpaceGame_DataStructures.hpp"

class Renderer {
  private:
    void PrepareTextureForPreRendering(SDL_Texture** texture, int width, int height);
  public:
    SDL_Window* window;
    SDL_Renderer* renderer;

    //Renderer();
    void CreateWindowAndRenderer();
    void PreRenderPlanetTexture(Planet* planet);
    void RenderPlanet(Planet planet);
    SDL_Texture* PreRenderDefaultStarTexture();
    SDL_Texture* PreRenderPlayButtonTexture();
    SDL_Texture* PreRenderHomeButtonTexture();
    SDL_Texture* PreRenderTitleTexture();
    SDL_Texture* PreRenderPauseTexture();
    SDL_Texture* PreRenderDeathTexture();
    SDL_Texture* PreRenderDigitTexture(int digit);
};