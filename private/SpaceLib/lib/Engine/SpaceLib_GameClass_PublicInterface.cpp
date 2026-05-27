#include "SpaceHeader.hpp"

void SpaceGame::GameInit() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL", nullptr);
    SDL_Quit();
    return;
  }

  game_renderer.CreateWindowAndRenderer();

  game_renderer.PreRenderDefaultStarTexture();
  game_renderer.PreRenderPlayButtonTexture();
  game_renderer.PreRenderHomeButtonTexture();
  game_renderer.PreRenderTitleTexture();

  main_menu.CreateMenu();
  main_menu.play_button.SetButtonTexture(game_renderer.play_button_texture);
  main_menu.title.SetTitleTexture(game_renderer.title_texture);
  

  pause_menu.play_button.SetButtonTexture(game_renderer.play_button_texture);
  pause_menu.home_button.SetButtonTexture(game_renderer.home_button_texture);
  death_screen.play_button.SetButtonTexture(game_renderer.play_button_texture);
  death_screen.home_button.SetButtonTexture(game_renderer.home_button_texture);

  Utils::CalculateOriginOffset();
  Utils::SetDisplayData();
  background.CreateBackground();

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
        main_menu.UpdateMenu(game_state, input);
        main_menu.RenderMenu(game_renderer.renderer);
        break;
      case STATE_PLAYING:
        HandlePlaying();
        game_screen.UpdateGameScreen(game_state, input);
        game_screen.RenderGameScreen(game_renderer);
        break;
      case STATE_PAUSE:
        HandlePause();
        pause_menu.RenderMenu(game_renderer.renderer);
        break;
      case STATE_DEATH_SCREEN:
        HandleDeathScreen();
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
  SDL_Quit();
}