#include "SpaceHeader.hpp"
/*
PlanetManager::PlanetManager() {
  this->asteroid_hit_planet = false;
}
*/
void PlanetManager::SetStarProperties() {
  planets[0].planet_radius = STAR_RADIUS;
  planets[0].orbit_radius = 0.0;
  planets[0].phase = 0.0;
  planets[0].planet_color = {255, 255, 255, 255};
  planets[0].planet_center.grid_x = 0.0;
  planets[0].planet_center.grid_y = 0.0;
  planets[0].orbit_speed = 0.0;
}

void PlanetManager::SetRandomProperties(Planet* planet) {
  //Assign random planet size and orbit
  planet->orbit_radius = Utils::MaxF(SDL_randf() * MAX_ORBIT_RADIUS, MIN_ORBIT_RADIUS);
  planet->planet_radius = Utils::MaxF((SDL_randf() * MAX_PLANET_RADIUS) + (planet->orbit_radius / 30.0), MIN_PLANET_RADIUS);
  planet->phase = SDL_randf();
  Utils::CalculatePlanetOrbitPosition(planet);
  
  //Assign random planet color
  int red = (int)SDL_rand(256);
  int green = (int)SDL_rand(256);
  int blue = (int)SDL_rand(256);
  planet->planet_color = {red, green, blue, 255};

  //Calculate planet orbit speed based on radius
  planet->orbit_speed = GRAVITATIONAL_CONSTANT / planet->orbit_radius;
  planet->being_moved = false;
}

bool PlanetManager::PlanetIsHovered(Planet planet, Input input) {
  GridPoint mouse_location = {
    .pixel_x = (int)input.mouse.pos_x,
    .pixel_y = (int)input.mouse.pos_y
  };
  Utils::CalculateGridCoordinates(&mouse_location);
  float distance_from_planet_center = SDL_sqrtf(
    SDL_powf(mouse_location.grid_x - planet.planet_center.grid_x, 2) + 
    SDL_powf(mouse_location.grid_y - planet.planet_center.grid_y, 2)
  );
  return distance_from_planet_center <= planet.planet_radius;
}

void PlanetManager::UpdatePlanetOrbits(AppState game_state) {
  for (int i = 1; i < PLANET_AMOUNT; i++) {
    if (!planets[i].being_moved) { 
      if (planets[i].orbit_radius > MAX_ORBIT_RADIUS) {
        float chage_speed_multiplier = planets[i].orbit_radius - MAX_ORBIT_RADIUS;
        planets[i].orbit_radius -= game_state.delta_time * chage_speed_multiplier;
        planets[i].orbit_speed = GRAVITATIONAL_CONSTANT / planets[i].orbit_radius;
        Utils::CalculatePlanetPhase(&planets[i]);
      }
      planets[i].phase += game_state.delta_time * planets[i].orbit_speed;
      Utils::CalculatePlanetOrbitPosition(&planets[i]);
    }
  }
}

void PlanetManager::ManualPlanetMove(AppState* game_state, Input input) {
  for (int i = 1; i < PLANET_AMOUNT; i++) {
    //Detect planet click
    if ((PlanetIsHovered(planets[i], input) && input.input_keys[MOUSE_BUTTON_LEFT].is_down) && !game_state->planet_being_moved) {
      planets[i].being_moved = true;
      game_state->planet_being_moved = true;
    }
    //Move planet if clicked
    if (planets[i].being_moved) {
      GridPoint mouse_location = {
        .pixel_x = (int)input.mouse.pos_x,
        .pixel_y = (int)input.mouse.pos_y
      };
      Utils::CalculateGridCoordinates(&mouse_location);
      planets[i].planet_center.grid_x = mouse_location.grid_x;
      planets[i].planet_center.grid_y = mouse_location.grid_y;
    }
    //Detect planet release
    if (planets[i].being_moved && ButtonReleased(MOUSE_BUTTON_LEFT)) {
      planets[i].being_moved = false;
      game_state->planet_being_moved = false;
      planets[i].orbit_radius = SDL_sqrtf(
        SDL_powf(planets[i].planet_center.grid_x, 2) + 
        SDL_powf(planets[i].planet_center.grid_y, 2)
      );
      planets[i].orbit_speed = GRAVITATIONAL_CONSTANT / planets[i].orbit_radius;
      Utils::CalculatePlanetPhase(&planets[i]);
    }
  }
}

void PlanetManager::SpawnAsteroid(AppState* game_state) {
  int random_planet_index = (int)SDL_rand(PLANET_AMOUNT - 1) + 1; //Randomly select a planet to spawn the asteroid around (excluding the star at index 0)
  if (!game_state->asteroid_is_active) {
    active_asteroid.asteroid_location.grid_x = planets[random_planet_index].planet_center.grid_x + (SDL_randf() - 0.5f) * 2.0f * ASTEROID_SPAWN_RADIUS_VARIANCE;
    active_asteroid.asteroid_location.grid_y = planets[random_planet_index].planet_center.grid_y + (SDL_randf() - 0.5f) * 2.0f * ASTEROID_SPAWN_RADIUS_VARIANCE;
    active_asteroid.asteroid_radius = Utils::MaxF(SDL_randf() * ASTEROID_MAX_RADIUS, ASTEROID_MIN_RADIUS);
    active_asteroid.indicator_radius = active_asteroid.asteroid_radius * 0.2f;
    active_asteroid.impact_timer = ASTEROID_TIMER_START;
    active_asteroid.asteroid_hit = false;
    game_state->asteroid_is_active = true;
  }
}

void PlanetManager::UpdateAsteroid(AppState* game_state) {
  active_asteroid.impact_timer -= game_state->delta_time;
  if (active_asteroid.impact_timer <= 0.0f) {
    active_asteroid.asteroid_hit = true;
    game_state->asteroid_is_active = false;
    return;
  }
  float indicator_fraction = Utils::InvLerpF(active_asteroid.impact_timer, 0.0f, ASTEROID_TIMER_START);
  active_asteroid.indicator_radius = Utils::LerpF(1.0f - indicator_fraction, active_asteroid.asteroid_radius * 0.2f, active_asteroid.asteroid_radius);
}

void PlanetManager::RenderAsteroid(SDL_Renderer* renderer) {
  Utils::CalculatePixelCoordinates(&active_asteroid.asteroid_location);
  SDL_FRect asteroid_rect = {
    active_asteroid.asteroid_location.pixel_x - (active_asteroid.asteroid_radius * BASE_UNIT_SIZE_PIXELS / Utils::grid_scale),
    active_asteroid.asteroid_location.pixel_y - (active_asteroid.asteroid_radius * BASE_UNIT_SIZE_PIXELS / Utils::grid_scale),
    active_asteroid.asteroid_radius * 2.0f * BASE_UNIT_SIZE_PIXELS / Utils::grid_scale,
    active_asteroid.asteroid_radius * 2.0f * BASE_UNIT_SIZE_PIXELS / Utils::grid_scale
  };
  SDL_SetTextureColorMod(planets[0].planet_texture, 119, 7, 21); //Reuse the defaut circular texture for the asteroid
  SDL_RenderTexture(renderer, planets[0].planet_texture, NULL, &asteroid_rect);
  SDL_FRect indicator_rect = {
    active_asteroid.asteroid_location.pixel_x - (active_asteroid.indicator_radius * BASE_UNIT_SIZE_PIXELS / Utils::grid_scale),
    active_asteroid.asteroid_location.pixel_y - (active_asteroid.indicator_radius * BASE_UNIT_SIZE_PIXELS / Utils::grid_scale),
    active_asteroid.indicator_radius * 2.0f * BASE_UNIT_SIZE_PIXELS / Utils::grid_scale,
    active_asteroid.indicator_radius * 2.0f * BASE_UNIT_SIZE_PIXELS / Utils::grid_scale
  };
  SDL_SetTextureColorMod(planets[0].planet_texture, 197, 7, 21);
  SDL_RenderTexture(renderer, planets[0].planet_texture, NULL, &indicator_rect);

  SDL_SetTextureColorMod(planets[0].planet_texture, 255, 255, 255); //Reset the texture color mod to default for future renders
}

void PlanetManager::RenderPlanets(Renderer game_renderer) {
  for (int i = 0; i < PLANET_AMOUNT; i++) {
    game_renderer.RenderPlanet(planets[i]);
  }
}

void PlanetManager::CheckAsteroidCollision() {
  for (int i = 1; i < PLANET_AMOUNT; i++) {
    float diff_x = planets[i].planet_center.grid_x - active_asteroid.asteroid_location.grid_x;
    float diff_y = planets[i].planet_center.grid_y - active_asteroid.asteroid_location.grid_y;
    float distance_from_planet_center = SDL_sqrtf((diff_x * diff_x) + (diff_y * diff_y));
    if ((distance_from_planet_center < active_asteroid.asteroid_radius + planets[i].planet_radius) && active_asteroid.asteroid_hit) {
      asteroid_hit_planet = true;
      break;
    }
  }
}

void PlanetManager::ResetGame(AppState* game_state, Renderer game_renderer) {
  SetStarProperties();
  game_renderer.PreRenderPlanetTexture(&planets[0]);
  for (int i = 1; i < PLANET_AMOUNT; i++) {
    SetRandomProperties(&planets[i]);
    game_renderer.PreRenderPlanetTexture(&planets[i]);
  }
  Utils::grid_scale = 2.0f;
  Utils::CalculateOriginOffset();
  game_state->planet_being_moved = false;
  game_state->asteroid_is_active = false;
  asteroid_hit_planet = false;
}

void PlanetManager::DestroyPlanetTextures() {
  for (int i = 0; i < PLANET_AMOUNT; i++) {
    SDL_DestroyTexture(planets[i].planet_texture);
  }
}