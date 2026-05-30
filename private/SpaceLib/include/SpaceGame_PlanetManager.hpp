#pragma once

#include "SpaceGame_DataStructures.hpp"
#include "SpaceGame_Macros.hpp"
#include "SpaceGame_Renderer.hpp"

class PlanetManager {
  private:
    Planet planets[PLANET_AMOUNT];
    Asteroid active_asteroid;
    bool PlanetIsHovered(Planet planet, Input input);
    void SetStarProperties();
    void SetRandomProperties(Planet* planet);
  public:
    //PlanetManager();
    bool asteroid_hit_planet;
    void SpawnAsteroid(AppState* game_state);
    void UpdateAsteroid(AppState* game_state);
    void UpdatePlanetOrbits(AppState game_state);
    void ManualPlanetMove(AppState* game_state, Input input);
    void CheckAsteroidCollision();
    void RenderAsteroid(SDL_Renderer* renderer);
    void RenderPlanets(Renderer game_renderer); 
    void ResetGame(AppState* game_state,Renderer game_renderer);
    void DestroyPlanetTextures();
};