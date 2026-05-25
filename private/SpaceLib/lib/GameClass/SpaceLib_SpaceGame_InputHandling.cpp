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

void SpaceGame::HandleSingleMouseButton(LogicalKeyCode key) {
  input.input_keys[key].has_changed = (input.input_keys[key].is_down != input.input_event.button.down);
  input.input_keys[key].is_down = input.input_event.button.down;
}

bool SpaceGame::ButtonPressed(LogicalKeyCode key) {
  return (input.input_keys[key].has_changed && input.input_keys[key].is_down);
}

bool SpaceGame::ButtonReleased(LogicalKeyCode key) {
  return (input.input_keys[key].has_changed && !input.input_keys[key].is_down);
}

void SpaceGame::HandleMouseScrollInput() {
  ChangeGridScale(-input.input_event.wheel.y);
}

void SpaceGame::HandleMouseMotionInput() {
  input.mouse.pos_x = input.input_event.motion.x;
  input.mouse.pos_y = input.input_event.motion.y;
}

void SpaceGame::ChangeGridScale(float step) {
  float scale_factor = 1.0 + (step * game_renderer.scale_change_sensitivity);
  game_renderer.grid_scale = ClampF(game_renderer.grid_scale * scale_factor, game_renderer.min_scale, game_renderer.max_scale);
  game_renderer.CalculateOriginOffset(); //Recalculate the grid origin position to center the frame with
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
          case SDLK_PLUS:
          case SDLK_KP_PLUS:
            HandleSingleButton(BUTTON_PLUS);
            ChangeGridScale(-1.0f);
            break;
          case SDLK_MINUS:
          case SDLK_KP_MINUS:
            HandleSingleButton(BUTTON_MINUS);
            ChangeGridScale(1.0f);
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
            HandleSingleMouseButton(MOUSE_BUTTON_LEFT);
            break;
          case SDL_BUTTON_RIGHT:
            HandleSingleMouseButton(MOUSE_BUTTON_RIGHT);
          default: break;
        }
        break;
      case SDL_EVENT_MOUSE_WHEEL: //Handle mouse scroll
        HandleMouseScrollInput();
        break;
      case SDL_EVENT_MOUSE_MOTION: //Handle mouse motion
        HandleMouseMotionInput();
        break;
      case SDL_EVENT_WINDOW_RESIZED:
        game_renderer.window_width = input.input_event.window.data1;
        game_renderer.window_height = input.input_event.window.data2;
        game_renderer.CalculateOriginOffset();
      default: break;
    }
  }
}