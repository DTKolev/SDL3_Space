#include "SpaceHeader.hpp"

void SpaceGame::SpawnAsteroid() {
  if (!game_state.asteroid_is_active) {
    active_asteroid.asteroid_location.grid_x = (SDL_randf() * 2.0f - 1.0f) * MAX_ORBIT_RADIUS;
    active_asteroid.asteroid_location.grid_y = (SDL_randf() * 2.0f - 1.0f) * MAX_ORBIT_RADIUS;
    active_asteroid.asteroid_radius = MaxF(SDL_randf() * 20.0f, 5.0f);
    active_asteroid.indicator_radius = active_asteroid.asteroid_radius * 0.2f;
    active_asteroid.impact_timer = ASTEROID_TIMER_START;
    active_asteroid.asteroid_hit = false;
    game_state.asteroid_is_active = true;
  }
}

void SpaceGame::UpdateAsteroid(Asteroid* asteroid) {
  asteroid->impact_timer -= game_state.delta_time;
  if (asteroid->impact_timer <= 0.0f) {
    asteroid->asteroid_hit = true;
    game_state.asteroid_is_active = false;
    return;
  }
  float indicator_fraction = InvLerpF(asteroid->impact_timer, 0.0f, ASTEROID_TIMER_START);
  asteroid->indicator_radius = LerpF(1.0f - indicator_fraction, asteroid->asteroid_radius * 0.2f, asteroid->asteroid_radius);
}

void SpaceGame::RenderAsteroid(Asteroid asteroid) {
  game_renderer.CalculatePixelCoordinates(&asteroid.asteroid_location);
  SDL_FRect asteroid_rect = {
    asteroid.asteroid_location.pixel_x - (asteroid.asteroid_radius * game_renderer.grid_scale),
    asteroid.asteroid_location.pixel_y - (asteroid.asteroid_radius * game_renderer.grid_scale),
    asteroid.asteroid_radius * 2.0f * game_renderer.grid_scale,
    asteroid.asteroid_radius * 2.0f * game_renderer.grid_scale
  };
  SDL_SetTextureColorMod(planets[0].planet_texture, 119, 7, 21); //Reuse the defaut circular texture for the asteroid
  SDL_RenderTexture(game_renderer.renderer, planets[0].planet_texture, NULL, &asteroid_rect);
  SDL_FRect indicator_rect = {
    asteroid.asteroid_location.pixel_x - (asteroid.indicator_radius * game_renderer.grid_scale),
    asteroid.asteroid_location.pixel_y - (asteroid.indicator_radius * game_renderer.grid_scale),
    asteroid.indicator_radius * 2.0f * game_renderer.grid_scale,
    asteroid.indicator_radius * 2.0f * game_renderer.grid_scale
  };
  SDL_SetTextureColorMod(planets[0].planet_texture, 197, 7, 21);
  SDL_RenderTexture(game_renderer.renderer, planets[0].planet_texture, NULL, &indicator_rect);

  SDL_SetTextureColorMod(planets[0].planet_texture, 255, 255, 255); //Reset the texture color mod to default for future renders
}

void SpaceGame::CheckAsteroidCollision() {
  for (int i = 1; i < PLANET_AMOUNT; i++) {
    float distance_from_planet_center = SDL_sqrtf(
      SDL_powf(active_asteroid.asteroid_location.grid_x - planets[i].planet_center.grid_x, 2.0f) + 
      SDL_powf(active_asteroid.asteroid_location.grid_y - planets[i].planet_center.grid_y, 2.0f)
    );
    if ((distance_from_planet_center < active_asteroid.asteroid_radius + planets[i].planet_radius) && active_asteroid.asteroid_hit) {
      game_state.current_state = STATE_DEATH_SCREEN;
      break;
    }
  }
}