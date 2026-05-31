#pragma once

#define BASE_UNIT_SIZE_PIXELS 20

#define PLANET_AMOUNT 10
#define BACKGROUND_STAR_AMOUNT 1000

#define SCREEN_BUTTON_SIZE 180.0f

#define ButtonPressed(key) (input.input_keys[key].is_down && input.input_keys[key].has_changed)
#define ButtonReleased(key) (!input.input_keys[key].is_down && input.input_keys[key].has_changed )