#include "SpaceHeader.hpp"

void SpaceGame::CalculateDeltaTime() {
  game_state.frame_end_time = SDL_GetPerformanceCounter();
  game_state.delta_time = (double)(game_state.frame_end_time - game_state.frame_begin_time) / (double)game_state.performance_frequency;
  game_state.frame_begin_time = game_state.frame_end_time;
}