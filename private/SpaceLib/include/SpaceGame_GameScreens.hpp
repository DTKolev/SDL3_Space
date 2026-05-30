#pragma once

#include "SpaceGame_DataStructures.hpp"
#include "SpaceGame_Macros.hpp"
#include "SpaceGame_Buttons.hpp"
#include "SpaceGame_Renderer.hpp"
#include "SpaceGame_VisualElements.hpp"
#include "SpaceGame_PlanetManager.hpp"

class MainMenu {
  public:
    PlayButton play_button;
    GameTitle title;
    //MainMenu();
    void ResetButtons();
    void CreateMenu();
    void UpdateMenu(AppState game_state);
    void RenderMenu(SDL_Renderer* renderer);  
};

class GameScreen {
  public:
    PlanetManager planet_manager;
    void CreateGameScreen(AppState* game_state, Renderer game_renderer);
    void UpdateGameScreen(AppState* game_state, Input input);
    void RenderGameScreen(Renderer game_renderer);
};

class PauseMenu {
  public:
    Title pause_title;
    PlayButton play_button;
    HomeButton home_button;
    //PauseMenu();
    void ResetButtons();
    void CreateMenu();
    void UpdateMenu();
    void RenderMenu(SDL_Renderer* renderer);
};

class DeathScreen {
  public:
    Title death_title;
    PlayButton play_button;
    HomeButton home_button;
    //DeathScreen();
    void CreateMenu();
    void ResetButtons();
    void UpdateMenu();
    void RenderMenu(SDL_Renderer* renderer);
};