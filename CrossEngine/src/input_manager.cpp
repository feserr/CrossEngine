/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "crossengine/input_manager.h"

// #include "../common/entry/input.h"

namespace CrossEngine {
InputManager::InputManager() : mouse_coords_(0.0f) {}

InputManager::~InputManager() {}

void InputManager::Update() {
  // Loop through key_map_ using a for each loop, and copy it over to
  // previous_key_map_
  for (auto& it : key_map_) {
    previous_key_map_[it.first] = it.second;
  }
}

void InputManager::PressKey(unsigned int key_id) {
  // Here we are treating key_map_ as an associative array.
  // if key_id doesn't already exist in key_map_, it will get added
  key_map_[key_id] = true;
}

void InputManager::ReleaseKey(unsigned int key_id) { key_map_[key_id] = false; }

void InputManager::SetMouseCoords(float x, float y) {
  mouse_coords_.x = x;
  mouse_coords_.y = y;
}

bool InputManager::IsKeyDown(unsigned int key_id) {
  // We dont want to use the associative array approach here
  // because we don't want to create a key if it doesnt exist.
  // So we do it manually
  auto it = key_map_.find(key_id);
  if (it != key_map_.end()) {
    // Found the key
    return it->second;
  } else {
    // Didn't find the key
    return false;
  }
}

bool InputManager::IsKeyDown(entry::Key::Enum key_id) {
  return inputGetKeyState(key_id);
}

bool InputManager::IsKeyPressed(unsigned int key_id) {
  // Check if it is pressed this frame, and wasn't pressed last frame
  if (IsKeyDown(key_id) == true && WasKeyDown(key_id) == false) {
    return true;
  }
  return false;
}

bool InputManager::WasKeyDown(unsigned int key_id) {
  // We dont want to use the associative array approach here
  // because we don't want to create a key if it doesnt exist.
  // So we do it manually
  auto it = previous_key_map_.find(key_id);
  if (it != previous_key_map_.end()) {
    // Found the key
    return it->second;
  } else {
    // Didn't find the key
    return false;
  }
}
}  // namespace CrossEngine
