#pragma once

#include "SpaceGame_DataStructures.hpp"

class Utils {
  public:
    static int window_width, window_height; //Window dimensions in pixels
    static float origin_offset_x, origin_offset_y; //Grid origin windowspace offset in grid units

    static constexpr float scale_change_sensitivity = 0.1;
    static constexpr float min_scale = 0.1;
    static constexpr float max_scale = 10.0;

    static float grid_scale;
    static DisplayData display_data;

    static float ClampF(float value, float min, float max);
    static float MaxF(float value1, float value2);
    static float InvLerpF(float value, float min, float max);
    static float LerpF(float fraction, float min, float max);

    static void SetDisplayData();
    static void CalculateOriginOffset();
    static void ChangeGridScale(float step);

    static void CalculatePixelCoordinates(GridPoint* point);
    static void CalculateGridCoordinates(GridPoint* point);

    static void CalculatePlanetOrbitPosition(Planet* planet);
    static void CalculatePlanetPhase(Planet* planet);

    static void CalculateDeltaTime(AppState* game_state);
};