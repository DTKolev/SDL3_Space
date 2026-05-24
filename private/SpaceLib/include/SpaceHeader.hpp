#pragma once
//---------------------- EXTERNAL DEPENDANCIES
#include <SDL3/SDL.h>
#include <iostream>
#include <vector>

//---------------------- PRE-PROCESSOR DEFINITIONS
#define BASE_UNIT_SIZE_PIXELS 20

#define PLANET_AMOUNT 10
#define MIN_PLANET_RADIUS 2.0f
#define MAX_PLANET_RADIUS 6.0f
#define MIN_ORBIT_RADIUS 30.0f
#define MAX_ORBIT_RADIUS 300.0f
#define STAR_RADIUS 10.0f
#define GRAVITATIONAL_CONSTANT 5.0f

#define BACKGROUND_STAR_AMOUNT 1000
#define MIN_BACKGROUND_STAR_SPEED 15.0f
#define MAX_BACKGROUND_STAR_SPEED 30.0f
#define MIN_BACKGROUND_STAR_BRIGHTNESS 0.2f

#define SCREEN_BUTTON_SIZE 180.0f
#define TITLE_WIDTH 580.0f
#define TITLE_HEIGHT TITLE_WIDTH * 57.0f / 87.0f

//---------------------- TYPE DEFINITIONS

//---------------------- ENUMERATORS
typedef enum {
  STATE_MENU,
  STATE_PLAYING,
  STATE_PAUSE,
  STATE_EXIT
} GameState;

typedef enum {
  BUTTON_P,
  BUTTON_R,
  BUTTON_Q,
  BUTTON_RETURN,
  BUTTON_ESCAPE,
  BUTTON_PLUS,
  BUTTON_MINUS,
  MOUSE_BUTTON_LEFT,
  MOUSE_BUTTON_RIGHT,
  button_amount
} LogicalKeyCode;

//---------------------- STRUCTS
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
  SDL_DisplayID display_id;
  const SDL_DisplayMode* display_mode;
} DisplayData;

typedef struct {
  DisplayData display_data;
  Uint64 frame_begin_time, frame_end_time, performance_frequency;
  GameState current_state;
  double delta_time;
  bool game_running;
  bool planet_being_moved;
  int moved_planet_index;
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
  float impact_timer;
}Asteroid;

typedef struct {
  SDL_FPoint star_location; //Star screenspace location
  float star_speed;
  int star_brightness;
}BackgroundStar;

//---------------------- SUPPORT CLASSES
class Renderer {
  private:
    void PrepareTextureForPreRendering(SDL_Texture** texture, int width, int height);
  public:
    const float scale_change_sensitivity = 0.1;
    const float min_scale = 0.1;
    const float max_scale = 10.0;

    float origin_offset_x, origin_offset_y; //Grid origin windowspace offset in grid units

    int window_width, window_height; //Window dimensions in pixels
    float grid_scale;
    double title_color_shift;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* default_star_texture;
    SDL_Texture* play_button_texture;
    SDL_Texture* home_button_texture;
    SDL_Texture* title_texture;

    void CalculateOriginOffset();

    //Point coordinates conversion from coordinate space to window space
    void CalculatePixelCoordinates(GridPoint* point);
    void CalculateGridCoordinates(GridPoint* point);

    //Planet rendering helper functions
    void PreRenderDefaultStarTexture();
    void PreRenderPlayButtonTexture();
    void PreRenderHomeButtonTexture();
    void PreRenderTitleTexture();
    void PreRenderPlanetTexture(Planet* planet);
    void RenderPlanet(Planet planet);

    //Class constructor
    Renderer();
};

//---------------------- GAME CLASS
class SpaceGame {
  private:
    //Internal variables
    AppState game_state;
    Renderer game_renderer;
    Input input;
    Planet planets[PLANET_AMOUNT];
    BackgroundStar background_stars[BACKGROUND_STAR_AMOUNT];

    //Input handling
    void ResetButtonStates();
    void HandleSingleButton(LogicalKeyCode key);
    void HandleSingleMouseButton(LogicalKeyCode key);
    bool ButtonPressed(LogicalKeyCode key);
    bool ButtonReleased(LogicalKeyCode key);
    void HandleMouseScrollInput();
    void HandleMouseMotionInput();
    void ChangeGridScale(float step);
    void HandleInput();

    //State machine
    void HandleMenu();
    void HandlePlaying();
    void HandlePause();

    //Screen rendering
    void RenderMenu();
    void RenderPlaying();
    void RenderPause();

    //Game utility functions
    void SetRandomProperties(Planet* planet);
    void CalculatePlanetOrbitPosition(Planet* planet);
    void CalculatePlanetPhase(Planet* planet);
    void ClearPlanetTextures();
    void UpdatePlanetOrbits();
    void RenderPlanets();
    bool PlanetIsHovered(Planet planet);
    void ManualPlanetMove();

    //Gameplay utility functions
    Asteroid SpawnAsteroid();

    //Visual element rendering
    void CreateBackground();
    void RenderBackground();
    void RenderPlayButton(float play_button_x, float play_button_y);
    void RenderHomeButton(float home_button_x, float home_button_y);
    void RenderTitle();
    //Delta time calculation
    void CalculateDeltaTime();

    //Helper math functions
    float ClampF(float value, float min, float max);
    float MaxF(float value1, float value2);
    float InvLerpF(float value, float min, float max);
  public:
    void GameInit();
    void GameRun();
    void GameTerminate();
};