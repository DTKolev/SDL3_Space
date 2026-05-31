#include <SDL3/SDL.h>

#include "SpaceGame_Engine.hpp"
#include "SpaceGame_Utils.hpp"

void SpaceGame::GameInit() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL", nullptr);
    SDL_Quit();
    return;
  }

  game_renderer.CreateWindowAndRenderer();

  main_menu.CreateMenu();
  main_menu.play_button.SetButtonTexture(game_renderer.PreRenderPlayButtonTexture());
  main_menu.title.SetTitleTexture(game_renderer.PreRenderTitleTexture());

  game_screen.score_counter.SetDigitTextures(game_renderer);
  
  pause_menu.CreateMenu();
  pause_menu.pause_title.SetTitleTexture(game_renderer.PreRenderPauseTexture());
  pause_menu.play_button.SetButtonTexture(game_renderer.PreRenderPlayButtonTexture());
  pause_menu.home_button.SetButtonTexture(game_renderer.PreRenderHomeButtonTexture());

  death_screen.CreateMenu();
  death_screen.death_title.SetTitleTexture(game_renderer.PreRenderDeathTexture());
  death_screen.play_button.SetButtonTexture(game_renderer.PreRenderPlayButtonTexture());
  death_screen.home_button.SetButtonTexture(game_renderer.PreRenderHomeButtonTexture());

  Utils::CalculateOriginOffset();
  Utils::SetDisplayData();
  background.CreateBackground();
  background.SetStarTexture(game_renderer.PreRenderDefaultStarTexture());

  game_state.asteroid_is_active = false;
  game_state.game_running = true;
  game_state.current_state = STATE_MENU;
  game_state.performance_frequency = SDL_GetPerformanceFrequency();
  game_state.frame_begin_time = SDL_GetPerformanceCounter();
  game_state.delta_time = 0.016;
}

void SpaceGame::GameRun() {
  while (game_state.game_running) {
    
    HandleInput();
    
    SDL_SetRenderDrawColor(game_renderer.renderer, 0, 0, 0, 255);
    SDL_RenderClear(game_renderer.renderer);
    
    background.UpdateAndRenderBackground(game_state, game_renderer);
    
    switch (game_state.current_state) {
      case STATE_MENU:
        HandleMenu();
        main_menu.UpdateMenu(game_state);
        main_menu.RenderMenu(game_renderer.renderer);
        break;
      case STATE_PLAYING:
        HandlePlaying();
        game_screen.UpdateGameScreen(&game_state, input);
        game_screen.RenderGameScreen(game_renderer);
        break;
      case STATE_PAUSE:
        HandlePause();
        pause_menu.UpdateMenu();
        pause_menu.RenderMenu(game_renderer.renderer);
        break;
      case STATE_DEATH_SCREEN:
        HandleDeathScreen();
        death_screen.UpdateMenu();
        death_screen.RenderMenu(game_renderer.renderer);
        break;
      case STATE_EXIT:
        game_state.game_running = false;
        break;
    }
    SDL_RenderPresent(game_renderer.renderer);
    Utils::CalculateDeltaTime(&game_state);
  }
}

void SpaceGame::GameTerminate() {
  game_screen.planet_manager.DestroyPlanetTextures();
  main_menu.title.DestroyTexture();
  main_menu.play_button.DestroyTexture();
  pause_menu.play_button.DestroyTexture();
  pause_menu.home_button.DestroyTexture();
  death_screen.play_button.DestroyTexture();
  death_screen.home_button.DestroyTexture();
  SDL_DestroyRenderer(game_renderer.renderer);
  SDL_DestroyWindow(game_renderer.window);
  SDL_Quit();
}