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
  planet->being_moved = false;
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
    if (!planets[i].being_moved) {
      planets[i].phase += game_state.delta_time * planets[i].orbit_speed;
      CalculatePlanetOrbitPosition(&planets[i]);
    }
  }
}

bool SpaceGame::PlanetIsHovered(Planet planet) {
  GridPoint mouse_location = {
    .pixel_x = (int)input.mouse.pos_x,
    .pixel_y = (int)input.mouse.pos_y
  };
  game_renderer.CalculateGridCoordinates(&mouse_location);
  float distance_from_planet_center = SDL_sqrtf(
    SDL_powf(mouse_location.grid_x - planet.planet_center.grid_x, 2) + 
    SDL_powf(mouse_location.grid_y - planet.planet_center.grid_y, 2)
  );
  return distance_from_planet_center <= planet.planet_radius;
}

void SpaceGame::ManualPlanetMove() {
  for (int i = 1; i < PLANET_AMOUNT; i++) {
    if (PlanetIsHovered(planets[i]) && input.input_keys[MOUSE_BUTTON_LEFT].is_down) {
      GridPoint mouse_location = {
        .pixel_x = (int)input.mouse.pos_x,
        .pixel_y = (int)input.mouse.pos_y
      };
      game_renderer.CalculateGridCoordinates(&mouse_location);
      planets[i].planet_center.grid_x = mouse_location.grid_x;
      planets[i].planet_center.grid_y = mouse_location.grid_y;
      planets[i].being_moved = true;
    }
    else if (PlanetIsHovered(planets[i]) && ButtonReleased(MOUSE_BUTTON_LEFT)) {
      planets[i].being_moved = false;
      planets[i].orbit_radius = SDL_sqrtf(
        SDL_powf(planets[i].planet_center.grid_x, 2) + 
        SDL_powf(planets[i].planet_center.grid_y, 2)
      );
      planets[i].orbit_speed = GRAVITATIONAL_CONSTANT / planets[i].orbit_radius;
    }
  }
}