#include "SpaceHeader.hpp"


int Utils::window_width = 1080;
int Utils::window_height = 720;
float Utils::origin_offset_x = 0.0f;
float Utils::origin_offset_y = 0.0f;
float Utils::grid_scale = 2.0f;
DisplayData Utils::display_data = {
  .display_mode = SDL_GetDesktopDisplayMode(SDL_GetPrimaryDisplay())
};

float Utils::ClampF(float value, float min, float max) {
  if (value < min) return min;
  if (value > max) return max;
  return value;
}

float Utils::MaxF(float value1, float value2) {
  return value1 > value2 ? value1 : value2;
}

float Utils::InvLerpF(float value, float min, float max) {
  return (value - min) / (max - min);
}

float Utils::LerpF(float fraction, float min, float max) {
  return min + fraction * (max - min);
}

void Utils::CalculateOriginOffset() {
  origin_offset_x = ((float)window_width * grid_scale) / (2.0 * (float)BASE_UNIT_SIZE_PIXELS);
  origin_offset_y = ((float)window_height * grid_scale) / (2.0 * (float)BASE_UNIT_SIZE_PIXELS);
}

void Utils::ChangeGridScale(float step) {
  float scale_factor = 1.0 + (step * scale_change_sensitivity);
  grid_scale = ClampF(grid_scale * scale_factor, min_scale, max_scale);
  CalculateOriginOffset(); //Recalculate the grid origin position to center the frame with
}

void Utils::CalculatePixelCoordinates(GridPoint* point) {
  float point_offset_x, point_offset_y; //Point windowspace offset in grid units
  point_offset_x = origin_offset_x + point->grid_x;
  point_offset_y = origin_offset_y - point->grid_y;
  point->pixel_x = (int)((point_offset_x * (float)BASE_UNIT_SIZE_PIXELS) / grid_scale);
  point->pixel_y = (int)((point_offset_y * (float)BASE_UNIT_SIZE_PIXELS) / grid_scale);
}

void Utils::CalculateGridCoordinates(GridPoint* point) {
  float point_offset_x, point_offset_y; //Point windowspace offset in grid units
  point_offset_x = ((float)point->pixel_x * grid_scale) / (float)BASE_UNIT_SIZE_PIXELS;
  point_offset_y = ((float)point->pixel_y * grid_scale) / (float)BASE_UNIT_SIZE_PIXELS;
  point->grid_x = (origin_offset_x - point_offset_x) * -1.0;
  point->grid_y = origin_offset_y - point_offset_y;
}

void Utils::CalculatePlanetOrbitPosition(Planet* planet) {
  planet->planet_center.grid_x = planet->orbit_radius * (float)SDL_cos((double)(planet->phase * SDL_PI_F * 2.0));
  planet->planet_center.grid_y = planet->orbit_radius * (float)SDL_sin((double)(planet->phase * SDL_PI_F * 2.0));
}

void Utils::CalculatePlanetPhase(Planet* planet) {
  planet->phase = SDL_atan2(planet->planet_center.grid_y, planet->planet_center.grid_x) / (SDL_PI_F * 2.0f);
  if (planet->phase < 0.0f) planet->phase += 1.0f; //Ensure the phase is in the range of 0-1
}

void Utils::CalculateDeltaTime(AppState* game_state) {
  game_state->frame_end_time = SDL_GetPerformanceCounter();
  game_state->delta_time = (double)(game_state->frame_end_time - game_state->frame_begin_time) / (double)game_state->performance_frequency;
  game_state->frame_begin_time = game_state->frame_end_time;
}