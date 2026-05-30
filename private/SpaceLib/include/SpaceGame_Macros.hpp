#pragma once

#define BASE_UNIT_SIZE_PIXELS 20

#define PLANET_AMOUNT 10
#define BACKGROUND_STAR_AMOUNT 1000

#define STAR_RADIUS 25.0f
#define GRAVITATIONAL_CONSTANT 5.0f

#define SCREEN_BUTTON_SIZE 180.0f
#define TITLE_WIDTH 580.0f
#define TITLE_HEIGHT TITLE_WIDTH * 57.0f / 87.0f
#define PAUSE_TITLE_WIDTH 580.0f
#define PAUSE_TITLE_HEIGHT PAUSE_TITLE_WIDTH * 27.0f / 87.0f
#define DEATH_TITLE_WIDTH 860.0f
#define DEATH_TITLE_HEIGHT DEATH_TITLE_WIDTH * 27.0f / 129.0f

#define ButtonPressed(key) (input.input_keys[key].is_down && input.input_keys[key].has_changed)
#define ButtonReleased(key) (!input.input_keys[key].is_down && input.input_keys[key].has_changed )