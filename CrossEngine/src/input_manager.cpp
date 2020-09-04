/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "crossengine/input_manager.h"

namespace CrossEngine {
InputManager::InputManager() : mouse_coords_(0.0f) {}

InputManager::~InputManager() {}

void InputManager::Update() {
  for (auto& it : key_map_) {
    previous_key_map_[it.first] = it.second;
  }
}

void InputManager::PressKey(entry::Key::Enum key_id) {
  key_map_[key_id] = true;
}

void InputManager::ReleaseKey(entry::Key::Enum key_id) {
  key_map_[key_id] = false;
}

void InputManager::SetMouseCoords(float x, float y) {
  mouse_coords_.x = x;
  mouse_coords_.y = y;
}

bool InputManager::IsKeyDown(entry::Key::Enum key_id) {
  bool state = inputGetKeyState(key_id);
  if (state == true) {
    key_map_[key_id] = true;
    return true;
  } else {
    key_map_[key_id] = false;
    return false;
  }
}

bool InputManager::IsKeyPressed(entry::Key::Enum key_id) {
  if (IsKeyDown(key_id) == true && WasKeyDown(key_id) == false) {
    return true;
  }
  return false;
}

bool InputManager::WasKeyDown(entry::Key::Enum key_id) {
  return previous_key_map_[key_id];
}
}  // namespace CrossEngine
