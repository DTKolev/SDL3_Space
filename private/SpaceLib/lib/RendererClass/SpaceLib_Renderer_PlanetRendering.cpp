#include "SpaceHeader.hpp"

void Renderer::PreRenderPlanetTexture(Planet* planet) {
  int radius = 50;
  int diameter = 100;

  //Create the planet texture
  planet->planet_texture = nullptr;
  planet->planet_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, diameter, diameter);
  if (planet->planet_texture == nullptr) return; //Stop executing the function if the texture isn't created successfully

  //Set texture properties
  SDL_SetTextureBlendMode(planet->planet_texture, SDL_BLENDMODE_BLEND);
  SDL_SetTextureScaleMode(planet->planet_texture, SDL_SCALEMODE_LINEAR);

  //Store the old render target (the game window in this case)
  SDL_Texture* old_render_target = SDL_GetRenderTarget(renderer); 
  
  //Set the new render target (the current planet's texture)
  SDL_SetRenderTarget(renderer, planet->planet_texture);

  //Fill texture with transparent color and set render draw color
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, planet->planet_color.r, planet->planet_color.g, planet->planet_color.b, planet->planet_color.a);

  //Draw a filled circle on the texture
  int x = radius - 1;
  int y = 0;
  int tx = 1;
  int ty = 1;
  int error = tx - diameter;
  while (x > y) {
    SDL_RenderLine(renderer, radius - x, radius - y, radius + x, radius - y);
    SDL_RenderLine(renderer, radius - x, radius + y, radius + x, radius + y);
    SDL_RenderLine(renderer, radius - y, radius - x, radius + y, radius - x);
    SDL_RenderLine(renderer, radius - y, radius + x, radius + y, radius  + x);

    if (error <= 0) { //The drawn lines are within the circle boundaries >> continue drawing lines of the same length
      y++;
      error += ty;
      ty += 2;
    }
    else { //The drawn lines have stepped outside the circle boundaries >> adjust the line lengths before moving onto the next step
      x--;
      tx += 2;
      error += (tx - (diameter));
    }
  }

  //Restore the old render target
  SDL_SetRenderTarget(renderer, old_render_target);
}

void Renderer::RenderPlanet(Planet planet) {
  int planet_radius_pixels = planet.planet_radius * BASE_UNIT_SIZE_PIXELS / grid_scale;
  CalculatePixelCoordinates(&planet.planet_center);

  //Create the destination FRect
  SDL_Rect destination_rect_int = {
    planet.planet_center.pixel_x - planet_radius_pixels,
    planet.planet_center.pixel_y - planet_radius_pixels,
    planet_radius_pixels * 2,
    planet_radius_pixels * 2 
  };
  SDL_FRect destination_rect_float;
  SDL_RectToFRect(&destination_rect_int, &destination_rect_float);

  //Render the planet texture
  SDL_RenderTexture(renderer, planet.planet_texture, NULL, &destination_rect_float);
}

void Renderer::PreRenderDefaultStarTexture() {
  default_star_texture = nullptr;
  default_star_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 10, 10);
  if (default_star_texture == nullptr) return; //Stop executing the function if the texture isn't created successfully

  //Set texture properties
  SDL_SetTextureBlendMode(default_star_texture, SDL_BLENDMODE_BLEND);
  SDL_SetTextureScaleMode(default_star_texture, SDL_SCALEMODE_LINEAR);

  //Store the old render target (the game window in this case)
  SDL_Texture* old_render_target = SDL_GetRenderTarget(renderer);
  //Set the new render target (the default star texture)
  SDL_SetRenderTarget(renderer, default_star_texture);

  //Fill texture with transparent color and set render draw color
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  int center_brightness = 255;
  SDL_SetRenderDrawColor(renderer, center_brightness, center_brightness, center_brightness, 255);

  //Draw a four-sided star shape on the texture
  for (int i = 0; i < 5; i++) {
    SDL_FPoint points[4] = {
      {5.0f + i, 5.0f},
      {5.0f - i, 5.0f},
      {5.0f, 5.0f + i},
      {5.0f, 5.0f - i}  
    };
    for (int j = 0; j < 4; j++) {
      SDL_RenderPoint(renderer, points[j].x, points[j].y);
    }
    center_brightness -= 50;
    SDL_SetRenderDrawColor(renderer, center_brightness, center_brightness, center_brightness, 255);
  }

  //Restore the old render target
  SDL_SetRenderTarget(renderer, old_render_target);
}