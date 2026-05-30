#pragma once

#include "SpaceGame_DataStructures.hpp"
#include "SpaceGame_Renderer.hpp"
#include "SpaceGame_GameScreens.hpp"
#include "SpaceGame_VisualElements.hpp"

class SpaceGame {
  private:
    AppState game_state;
    Renderer game_renderer;
    Input input;

    MainMenu main_menu;
    GameScreen game_screen;
    PauseMenu pause_menu;
    DeathScreen death_screen;
    Background background;

    void ResetButtonStates();
    void HandleSingleButton(LogicalKeyCode key);
    void HandleSingleMouseButton(LogicalKeyCode key);
    void HandleMouseMotionInput();
    void UpdateScreenButtonsStates();
    void HandleInput();

    void HandleMenu();
    void HandlePlaying();
    void HandlePause();
    void HandleDeathScreen();
  public:
    //SpaceGame();
    void GameInit();
    void GameRun();
    void GameTerminate();
};