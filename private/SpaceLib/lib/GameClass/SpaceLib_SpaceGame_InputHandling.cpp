#include "SpaceHeader.hpp"

void SpaceGame::ResetButtonStates() {
  for (int i = 0; i < button_amount; i++) {
    input.input_keys[i].has_changed = false;
  }
}

void SpaceGame::HandleSingleButton(LogicalKeyCode key) {
  input.input_keys[key].has_changed = (input.input_keys[key].is_down != input.input_event.key.down); 
  input.input_keys[key].is_down = input.input_event.key.down;
}

bool SpaceGame::ButtonPressed(LogicalKeyCode key) {
  return (input.input_keys[key].has_changed && input.input_keys[key].is_down);
}

bool SpaceGame::ButtonReleased(LogicalKeyCode key) {
  return (input.input_keys[key].has_changed && !input.input_keys[key].is_down);
}

void SpaceGame::HandleMouseScrollInput() {
  float mouse_scroll = -input.input_event.wheel.y;
  float scale_factor = 1.0 + (mouse_scroll * game_renderer.scale_change_sensitivity);

  game_renderer.grid_scale = ClampF(game_renderer.grid_scale * scale_factor, game_renderer.min_scale, game_renderer.max_scale);
  game_renderer.CalculateOriginOffset(); //Recalculate the grid origin position to center the frame with the new scale factor
}

void SpaceGame::HandleInput() {
  ResetButtonStates();
  while (SDL_PollEvent(&input.input_event)) {
    switch (input.input_event.type) {
      case SDL_EVENT_QUIT:
        game_state.game_running = false;
        break;
      case SDL_EVENT_KEY_UP: //Handle keyboard key press/release
      case SDL_EVENT_KEY_DOWN:
        switch (input.input_event.key.key) {
          case SDLK_P:
            HandleSingleButton(BUTTON_P);
            break;
          case SDLK_R:
            HandleSingleButton(BUTTON_R);
            break;
          case SDLK_Q:
            HandleSingleButton(BUTTON_Q);
            break;
          case SDLK_RETURN:
          case SDLK_RETURN2:
            HandleSingleButton(BUTTON_RETURN);
            break;
          case SDLK_ESCAPE:
            HandleSingleButton(BUTTON_ESCAPE);
            break;
          default: break;
        }
      case SDL_EVENT_MOUSE_BUTTON_UP: //Handle mouse button press/release
      case SDL_EVENT_MOUSE_BUTTON_DOWN:
        switch (input.input_event.button.button) {
          case SDL_BUTTON_LEFT:
            HandleSingleButton(MOUSE_BUTTON_LEFT);
            break;
          case SDL_BUTTON_RIGHT:
            HandleSingleButton(MOUSE_BUTTON_RIGHT);
          default: break;
        }
        input.mouse.pos_x = input.input_event.button.x; //Record mouse X and Y position (relative to window) at the time of press/release
        input.mouse.pos_y = input.input_event.button.y;
        break;
      case SDL_EVENT_MOUSE_WHEEL: //Handle mouse scroll
        HandleMouseScrollInput();
        break;
      case SDL_EVENT_WINDOW_RESIZED:
        game_renderer.window_width = input.input_event.window.data1;
        game_renderer.window_height = input.input_event.window.data2;
        game_renderer.CalculateOriginOffset();
      default: break;
    }
  }
}