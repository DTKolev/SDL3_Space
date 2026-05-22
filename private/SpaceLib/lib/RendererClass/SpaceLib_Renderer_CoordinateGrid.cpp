#include "SpaceHeader.hpp"

 void Renderer::CalculateOriginOffset() {
  origin_offset_x = ((float)window_width * grid_scale) / (2.0 * (float)BASE_UNIT_SIZE_PIXELS);
  origin_offset_y = ((float)window_height * grid_scale) / (2.0 * (float)BASE_UNIT_SIZE_PIXELS);
}

void Renderer::CalculatePixelCoordinates(GridPoint* point) {
  float point_offset_x, point_offset_y; //Point windowspace offset in grid units
  point_offset_x = origin_offset_x + point->grid_x;
  point_offset_y = origin_offset_y - point->grid_y;
  point->pixel_x = (int)((point_offset_x * (float)BASE_UNIT_SIZE_PIXELS) / grid_scale);
  point->pixel_y = (int)((point_offset_y * (float)BASE_UNIT_SIZE_PIXELS) / grid_scale);
}

void Renderer::CalculateGridCoordinates(GridPoint* point) {
  float point_offset_x, point_offset_y; //Point windowspace offset in grid units
  point_offset_x = ((float)point->pixel_x * grid_scale) / (float)BASE_UNIT_SIZE_PIXELS;
  point_offset_y = ((float)point->pixel_y * grid_scale) / (float)BASE_UNIT_SIZE_PIXELS;
  point->grid_x = (origin_offset_x - point_offset_x) * -1.0;
  point->grid_y = origin_offset_y - point_offset_y;
}