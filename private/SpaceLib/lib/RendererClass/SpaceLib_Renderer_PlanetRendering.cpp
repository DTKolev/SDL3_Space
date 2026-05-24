#include "SpaceHeader.hpp"

//Creates a texture with the spcified parameters and makes it the render target
void Renderer::PrepareTextureForPreRendering(SDL_Texture** texture, int width, int height) {
  *texture = nullptr;
  *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
  if (*texture == nullptr) return; //Stop executing the function if the texture isn't created successfully

  SDL_SetTextureBlendMode(*texture, SDL_BLENDMODE_BLEND);
  SDL_SetTextureScaleMode(*texture, SDL_SCALEMODE_LINEAR);

  SDL_SetRenderTarget(renderer, *texture);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
}

void Renderer::PreRenderPlanetTexture(Planet* planet) {
  int radius = 50;
  int diameter = 100;

  //Store the old render target (the game window in this case)
  SDL_Texture* old_render_target = SDL_GetRenderTarget(renderer);

  //Create the planet texture and set it as the new render target
  PrepareTextureForPreRendering(&planet->planet_texture, diameter, diameter);

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
  //Store the old render target (the game window in this case) and create the default star texture and set it as the new render target
  SDL_Texture* old_render_target = SDL_GetRenderTarget(renderer);
  PrepareTextureForPreRendering(&default_star_texture, 10, 10);
 
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

void Renderer::PreRenderPlayButtonTexture() {
  //Store the old render target (the game window in this case) and create the play button texture and set it as the new render target
  SDL_Texture* old_render_target = SDL_GetRenderTarget(renderer);
  PrepareTextureForPreRendering(&play_button_texture, 100, 100);

  SDL_Vertex vertecies[3] = {
    {{0.0f, 0.0f}, {255, 255, 255, 255}, {0.0f, 0.0f}},
    {{0.0f, 100.0f}, {255, 255, 255, 255}, {0.0f, 1.0f}},
    {{100.0f, 50.0f}, {255, 255, 255, 255}, {1.0f, 0.5f}}
  };

  SDL_RenderGeometry(renderer, NULL, vertecies, 3, NULL, 0);

  //Restore the old render target
  SDL_SetRenderTarget(renderer, old_render_target);
}

void Renderer::PreRenderHomeButtonTexture() {
  //Store the old render target (the game window in this case)
  SDL_Texture* old_render_target = SDL_GetRenderTarget(renderer);
  PrepareTextureForPreRendering(&home_button_texture, 100, 100);
  
  //Draw the home icon from a filled FRect for base and triangle roof
  SDL_FRect home_base = {10.0f, 40.0f, 80.0f, 60.0f};
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &home_base);
  SDL_Vertex roof_vertices[3] = {
    {{0.0f, 40.0f}, {255, 255, 255, 255}, {0.0f, 0.4f}},
    {{100.0f, 40.0f}, {255, 255, 255, 255}, {1.0f, 0.4f}},
    {{50.0f, 0.0f}, {255, 255, 255, 255}, {0.5f, 0.0f}}
  };
  SDL_RenderGeometry(renderer, NULL, roof_vertices, 3, NULL, 0);

  //Restore the old render target
  SDL_SetRenderTarget(renderer, old_render_target);
}

void Renderer::PreRenderTitleTexture() {
  SDL_Texture* old_render_target = SDL_GetRenderTarget(renderer);
  PrepareTextureForPreRendering(&title_texture, 87, 57);
  SDL_SetTextureScaleMode(title_texture, SDL_SCALEMODE_NEAREST);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  //Build the letter "S"
  SDL_FRect s_rects[5] = {
    {0.0f, 0.0f, 15.0f, 3.0f},
    {0.0f, 0.0f, 3.0f, 15.0f},
    {0.0f, 12.0f, 15.0f, 3.0f},
    {12.0f, 12.0f, 3.0f, 15.0f},
    {0.0f, 24.0f, 15.0f, 3.0f}
  };
  //Build the letter "P"
  SDL_FRect p_rects[4] = {
    {18.0f, 0.0f, 3.0f, 27.0f},
    {18.0f, 0.0f, 15.0f, 3.0f},
    {30.0f, 0.0f, 3.0f, 15.0f},
    {18.0f, 12.0f, 15.0f, 3.0f}
  };
  //Build the letter "A1"
  SDL_FRect a1_rects[4] = {
    {36.0f, 0.0f, 3.0f, 27.0f},
    {36.0f, 0.0f, 15.0f, 3.0f},
    {48.0f, 0.0f, 3.0f, 27.0f},
    {36.0f, 12.0f, 15.0f, 3.0f}
  };
  //Build the letter "C"
  SDL_FRect c_rects[3] = {
    {54.0f, 0.0f, 3.0f, 27.0f},
    {54.0f, 0.0f, 15.0f, 3.0f},
    {54.0f, 24.0f, 15.0f, 3.0f}
  };
  //Build the letter "E1"
  SDL_FRect e1_rects[4] = {
    {72.0f, 0.0f, 3.0f, 27.0f},
    {72.0f, 0.0f, 15.0f, 3.0f},
    {72.0f, 12.0f, 12.0f, 3.0f},
    {72.0f, 24.0f, 15.0f, 3.0f}
  };
  //Build the letter "G"
  SDL_FRect g_rects[5] = {
    {9.0f, 30.0f, 3.0f, 27.0f},
    {9.0f, 30.0f, 15.0f, 3.0f},
    {9.0f, 54.0f, 15.0f, 3.0f},
    {21.0f, 42.0f, 3.0f, 15.0f},
    {15.0f, 42.0f, 9.0f, 3.0f}
  };
  //Build the Letter "A2"
  SDL_FRect a2_rects[4] = {
    {27.0f, 30.0f, 3.0f, 27.0f},
    {27.0f, 30.0f, 15.0f, 3.0f},
    {39.0f, 30.0f, 3.0f, 27.0f},
    {27.0f, 42.0f, 15.0f, 3.0f}
  };
  //Build the letter "M"
  SDL_FRect m_rects[4] = {
    {45.0f, 30.0f, 3.0f, 27.0f},
    {45.0f, 30.0f, 15.0f, 3.0f},
    {57.0f, 30.0f, 3.0f, 27.0f},
    {51.0f, 30.0f, 3.0f, 18.0f}
  };
  //Build the letter "E2"
  SDL_FRect e2_rects[4] = {
    {63.0f, 30.0f, 3.0f, 27.0f},
    {63.0f, 30.0f, 15.0f, 3.0f},
    {63.0f, 42.0f, 12.0f, 3.0f},
    {63.0f, 54.0f, 15.0f, 3.0f}
  };

  SDL_RenderFillRects(renderer, s_rects, 5);
  SDL_RenderFillRects(renderer, p_rects, 4);
  SDL_RenderFillRects(renderer, a1_rects, 4);
  SDL_RenderFillRects(renderer, c_rects, 3);
  SDL_RenderFillRects(renderer, e1_rects, 4);
  SDL_RenderFillRects(renderer, g_rects, 5);
  SDL_RenderFillRects(renderer, a2_rects, 4);
  SDL_RenderFillRects(renderer, m_rects, 4);
  SDL_RenderFillRects(renderer, e2_rects, 4);

  SDL_SetRenderTarget(renderer, old_render_target);
}