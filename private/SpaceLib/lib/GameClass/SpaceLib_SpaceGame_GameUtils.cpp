#include "SpaceHeader.hpp"

void SpaceGame::SetRandomProperties(Planet* planet) {
  //Assign random planet size and orbit
  planet->orbit_radius = MaxF(SDL_randf() * MAX_ORBIT_RADIUS, MIN_ORBIT_RADIUS);
  planet->planet_radius = MaxF((SDL_randf() * MAX_PLANET_RADIUS) + (planet->orbit_radius / 30.0), MIN_PLANET_RADIUS);
  planet->phase = SDL_randf();
  CalculatePlanetOrbitPosition(planet);
  
  //Assign random planet color
  int red = (int)SDL_rand(256);
  int green = (int)SDL_rand(256);
  int blue = (int)SDL_rand(256);
  planet->planet_color = {red, green, blue, 255};

  //Calculate planet orbit speed based on radius
  planet->orbit_speed = GRAVITATIONAL_CONSTANT / planet->orbit_radius;
}

void SpaceGame::CalculatePlanetOrbitPosition(Planet* planet) {
  planet->planet_center.grid_x = planet->orbit_radius * (float)SDL_cos((double)(planet->phase * SDL_PI_F * 2.0));
  planet->planet_center.grid_y = planet->orbit_radius * (float)SDL_sin((double)(planet->phase * SDL_PI_F * 2.0));
}

void SpaceGame::ClearPlanetTextures() {
  for (int i = 0; i < PLANET_AMOUNT; i++) {
    SDL_DestroyTexture(planets[i].planet_texture);
  }
}

void SpaceGame::RenderPlanets() {
  for (int i = 0; i < PLANET_AMOUNT; i++) {
    game_renderer.RenderPlanet(planets[i]);
  }
}

void SpaceGame::UpdatePlanetOrbits() {
  for (int i = 1; i < PLANET_AMOUNT; i++) {
    planets[i].phase += game_state.delta_time * planets[i].orbit_speed;
    CalculatePlanetOrbitPosition(&planets[i]);
  }
}