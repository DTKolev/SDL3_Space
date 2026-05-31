#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_stdinc.h>
#include "SpaceGame_Enums.hpp"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

typedef struct {
  int r, g, b, a;
} ColorRGBA;

typedef struct {
  bool is_down, has_changed;
} Button;

typedef struct {
  float pos_x, pos_y;
} Mouse;

typedef struct {
  Button input_keys[button_amount];
  Mouse mouse;
  SDL_Event input_event;
  bool play_button_pressed, home_button_pressed;
} Input;

typedef struct {
  const SDL_DisplayMode* display_mode;
} DisplayData;

typedef struct {
  Uint64 frame_begin_time, frame_end_time, performance_frequency;
  GameState current_state;
  double delta_time;
  bool game_running;
  bool planet_being_moved;
  bool asteroid_is_active;
} AppState;

typedef struct {
  float grid_x, grid_y; //Grid coordinates in coordinate space
  int pixel_x, pixel_y; //Pixel coordinates in screen space
} GridPoint;

typedef struct {
  GridPoint planet_center;
  ColorRGBA planet_color;
  SDL_Texture* planet_texture;
  float planet_radius; //Planet radius in grid units
  float orbit_radius; //Orbit radius in grid units
  float phase; //Planet's progress along its orbit path in the range of 0-1
  float orbit_speed;
  bool being_moved;
} Planet;

typedef struct {
  GridPoint asteroid_location;
  float asteroid_radius; //Asteroid radius in grid units
  float indicator_radius;
  float impact_timer;
} Asteroid;

typedef struct {
  SDL_FPoint star_location; //Star screenspace location
  float star_speed;
  int star_brightness;
}BackgroundStar;