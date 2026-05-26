#pragma once
//---------------------- EXTERNAL DEPENDANCIES
#include <SDL3/SDL.h>
#include <iostream>
#include <vector>

//---------------------- PRE-PROCESSOR DEFINITIONS
#define BASE_UNIT_SIZE_PIXELS 20

#define PLANET_AMOUNT 10
#define MIN_PLANET_RADIUS 6.0f
#define MAX_PLANET_RADIUS 10.0f
#define MIN_ORBIT_RADIUS 50.0f
#define MAX_ORBIT_RADIUS 350.0f
#define ORBIT_RADIUS_CHANGE_SPEED 50.0f

#define STAR_RADIUS 25.0f
#define GRAVITATIONAL_CONSTANT 5.0f

#define BACKGROUND_STAR_AMOUNT 1000
#define MIN_BACKGROUND_STAR_SPEED 15.0f
#define MAX_BACKGROUND_STAR_SPEED 30.0f
#define MIN_BACKGROUND_STAR_BRIGHTNESS 0.2f

#define SCREEN_BUTTON_SIZE 180.0f
#define TITLE_WIDTH 580.0f
#define TITLE_HEIGHT TITLE_WIDTH * 57.0f / 87.0f

#define ASTEROID_SPAWN_RADIUS_VARIANCE 100.0f
#define ASTEROID_MAX_RADIUS 150.0f
#define ASTEROID_MIN_RADIUS 50.0f
#define ASTEROID_TIMER_START 5.0f

#define ButtonPressed(key) (input.input_keys[key].is_down && input.input_keys[key].has_changed)
#define ButtonReleased(key) (!input.input_keys[key].is_down && input.input_keys[key].has_changed )

//---------------------- TYPE DEFINITIONS

//---------------------- ENUMERATORS
typedef enum {
  STATE_MENU,
  STATE_PLAYING,
  STATE_PAUSE,
  STATE_DEATH_SCREEN,
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
  bool asteroid_hit;
} Asteroid;

typedef struct {
  SDL_FPoint star_location; //Star screenspace location
  float star_speed;
  int star_brightness;
}BackgroundStar;

//---------------------- SUPPORT CLASSES
class Utils {
  public:
    int window_width, window_height; //Window dimensions in pixels
    float origin_offset_x, origin_offset_y; //Grid origin windowspace offset in grid units

    const float scale_change_sensitivity = 0.1;
    const float min_scale = 0.1;
    const float max_scale = 10.0;

    float grid_scale;
    const SDL_DisplayMode* display_mode = SDL_GetDesktopDisplayMode(SDL_GetPrimaryDisplay());

    float ClampF(float value, float min, float max);
    float MaxF(float value1, float value2);
    float InvLerpF(float value, float min, float max);
    float LerpF(float fraction, float min, float max);

    void SetWindowSize(int width, int height);
    void SetGridScale(float scale);

    void CalculateOriginOffset();
    void ChangeGridScale(float step);

    void CalculatePixelCoordinates(GridPoint* point);
    void CalculateGridCoordinates(GridPoint* point);

    void CalculatePlanetOrbitPosition(Planet* planet);
    void CalculatePlanetPhase(Planet* planet);

    void CalculateDeltaTime(AppState* game_state);
};

class Renderer {
  private:
    Utils utils;
    void PrepareTextureForPreRendering(SDL_Texture** texture, int width, int height);
  public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* default_star_texture;
    SDL_Texture* play_button_texture;
    SDL_Texture* home_button_texture;
    SDL_Texture* title_texture;

    Renderer();
    void CreateWindowAndRenderer();
    void PreRenderPlanetTexture(Planet* planet);
    void RenderPlanet(Planet planet);
    void PreRenderDefaultStarTexture();
    void PreRenderPlayButtonTexture();
    void PreRenderHomeButtonTexture();
    void PreRenderTitleTexture();
    ~Renderer();
};

class PlanetManager {
  private:
    Utils utils;
    Planet planets[PLANET_AMOUNT];
    Asteroid active_asteroid;
    bool PlanetIsHovered(Planet planet, Input input);
    void SetStarProperties();
    void SetRandomProperties(Planet* planet);
  public:
    PlanetManager();
    bool asteroid_hit_planet;
    void SpawnAsteroid(AppState game_state);
    void UpdateAsteroid(AppState game_state);
    void UpdatePlanetOrbits(AppState game_state);
    void ManualPlanetMove(AppState game_state, Input input);
    void CheckAsteroidCollision();
    void RenderAsteroid(SDL_Renderer* renderer);
    void RenderPlanets(Renderer game_renderer); 
    void ResetGame(AppState game_state,Renderer game_renderer);
    ~PlanetManager();
};

class ScreenButton {
  protected:
    Utils utils;
    SDL_FRect button_rect;
    SDL_Texture* button_texture;
    bool is_hovered, is_pressed;
    virtual void SetButtonTexture(SDL_Texture* texture) = 0;
    virtual void CheckButtonState(Input input) = 0;
    virtual void ResetButtonState() = 0;
    virtual void Render(SDL_Renderer* renderer) = 0;
    virtual bool Pressed() = 0;
};

class PlayButton : public ScreenButton {
  public:
    PlayButton(float center_x, float center_y);
    void SetButtonTexture(SDL_Texture* texture);
    void CheckButtonState(Input input);
    void ResetButtonState();
    void Render(SDL_Renderer* renderer);
    bool Pressed();
};

class HomeButton : public ScreenButton {
  private:
    SDL_Texture* button_texture;
  public:
    HomeButton(float center_x, float center_y);
    void SetButtonTexture(SDL_Texture* texture);
    void CheckButtonState(Input input);
    void ResetButtonState();
    void Render(SDL_Renderer* renderer);
    bool Pressed();
};

class GameTitle {
  private:
    SDL_Texture* title_texture;
    SDL_FRect title_rect;
    double color_shift;
  public:
    GameTitle(float center_x, float center_y);
    void SetTitleTexture(SDL_Texture* texture);
    void UpdateTitle(double delta_time);
    void Render(SDL_Renderer* renderer);
};

class Background {
  private:
    Utils utils;
    BackgroundStar background_stars[BACKGROUND_STAR_AMOUNT];
    SDL_Texture* star_texture;
  public:
    Background();
    void SetStarTexture(SDL_Texture* texture);
    void UpdateAndRenderBackground(AppState game_state, Renderer game_renderer);
};

class MainMenu {
  private:
    Utils utils;
    GameTitle title;
  public:
    PlayButton play_button;
    MainMenu();
    void ResetButtons();
    void UpdateMenu(AppState game_state, Input input);
    void RenderMenu(SDL_Renderer* renderer);  
};

class GameScreen {
  private:
    PlanetManager planet_manager;
  public:
    void UpdateGameScreen(AppState game_state, Input input);
    void RenderGameScreen(Renderer game_renderer);
};

class PauseMenu {
  public:
    Utils utils;
    PlayButton play_button;
    HomeButton home_button;
    PauseMenu();
    void ResetButtons();
    void UpdateMenu(Input input);
    void RenderMenu(SDL_Renderer* renderer);
};

class DeathScreen {
  public:
    Utils utils;
    PlayButton play_button;
    HomeButton home_button;
    DeathScreen();
    void ResetButtons();
    void UpdateMenu(Input input);
    void RenderMenu(SDL_Renderer* renderer);
};

//---------------------- GAME CLASS

class SpaceGame {
  private:
    Utils utils;

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