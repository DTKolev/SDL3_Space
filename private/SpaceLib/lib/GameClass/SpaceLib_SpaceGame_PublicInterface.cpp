#include "SpaceHeader.hpp"

void SpaceGame::GameInit() {
  //Initialize SDL
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL", nullptr);
    SDL_Quit();
    return;
  }
  //Create widnow and renderer
  game_renderer.window = SDL_CreateWindow("Space Game  Window", game_renderer.window_width, game_renderer.window_height, SDL_WINDOW_RESIZABLE);
  game_renderer.renderer = SDL_CreateRenderer(game_renderer.window, NULL);
  if (game_renderer.window == nullptr || game_renderer.renderer == nullptr) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating window or renderer", game_renderer.window);
    SDL_DestroyRenderer(game_renderer.renderer);
    SDL_DestroyWindow(game_renderer.window);
    SDL_Quit();
    return;
  }

  //Get the display data
  game_state.display_data.display_id = SDL_GetDisplayForWindow(game_renderer.window);
  game_state.display_data.display_mode = SDL_GetDesktopDisplayMode(game_state.display_data.display_id);

  //Initialize the game grid
  game_renderer.grid_scale = 1.0f;
  game_renderer.CalculateOriginOffset();

  //Pre-render planets to the corresponding textures (planet 0 is the star located at grid origin)
  //Pre-render the star and place it it on the grid origin
  planets[0].planet_radius = STAR_RADIUS;
  planets[0].orbit_radius = 0.0;
  planets[0].phase = 0.0;
  planets[0].planet_color = {255, 255, 255, 255};
  planets[0].planet_center.grid_x = 0.0;
  planets[0].planet_center.grid_y = 0.0;
  planets[0].orbit_speed = 0.0;
  game_renderer.PreRenderPlanetTexture(&planets[0]);
  //Pre-render the remaining planets and place them on random positions
  for(int i = 1; i < PLANET_AMOUNT; i++) {
    SetRandomProperties(&planets[i]);
    game_renderer.PreRenderPlanetTexture(&planets[i]);
  }

  CreateBackground();

  //Set game loop variables
  game_state.game_running = true;
  game_state.current_state = STATE_MENU;
  game_state.performance_frequency = SDL_GetPerformanceFrequency();
  game_state.frame_begin_time = SDL_GetPerformanceCounter();
  game_state.delta_time = 0.016;
}

void SpaceGame::GameRun() {
  while (game_state.game_running) {
    HandleInput();
    switch (game_state.current_state) {
      case STATE_MENU:
        HandleMenu();
        break;
      case STATE_PLAYING:
        HandlePlaying();
        //game_renderer.RenderCurrentScreen(STATE_PLAYING);
        break;
      case STATE_PAUSE:
        HandlePause();
        //game_renderer.RenderCurrentScreen(STATE_PAUSE);
        break;
      case STATE_EXIT:
        game_state.game_running = false;
        break;
    }
    SDL_SetRenderDrawColor(game_renderer.renderer, 0, 0, 0, 0);
    SDL_RenderClear(game_renderer.renderer);
    UpdatePlanetOrbits();
    RenderBackground();
    RenderPlanets();
    SDL_RenderPresent(game_renderer.renderer);
    CalculateDeltaTime();
  }

}

void SpaceGame::GameTerminate() {
  ClearPlanetTextures();
  SDL_DestroyRenderer(game_renderer.renderer);
  SDL_DestroyWindow(game_renderer.window);
  SDL_Quit();
}