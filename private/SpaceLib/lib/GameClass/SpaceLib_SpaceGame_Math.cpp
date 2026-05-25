#include "SpaceHeader.hpp"

float SpaceGame::ClampF(float value, float min, float max) {
  if (value < min) return min;
  else if (value > max) return max;
  else return value;
}

float SpaceGame::MaxF(float value1, float value2) {
  return value1 > value2 ? value1: value2;
}

float SpaceGame::InvLerpF(float value, float min, float max) {
  return (value - min) / (max - min);
}

float SpaceGame::LerpF(float fraction, float min, float max) {
  return min + (max - min) * fraction;
}