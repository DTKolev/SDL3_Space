#pragma once

#include "SpaceGame_DataStructures.hpp"

class ScreenButton {
  protected:
    SDL_FRect button_rect;
    SDL_Texture* button_texture;
    bool is_hovered, is_pressed;
    virtual void CheckButtonState(Input input) = 0;
    virtual void Render(SDL_Renderer* renderer) = 0;
  public:
    void SetButtonTexture(SDL_Texture* texture);
    void CreateButton(float x, float y);
    void UpdateButtonLocation(float x, float y);
    void ResetButtonState();
    bool Pressed();
};

class PlayButton : public ScreenButton {
  public:
    void CheckButtonState(Input input);
    void Render(SDL_Renderer* renderer);
};

class HomeButton : public ScreenButton {
  public:
    void CheckButtonState(Input input);
    void Render(SDL_Renderer* renderer);
};