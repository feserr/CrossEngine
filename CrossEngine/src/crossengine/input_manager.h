/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_INPUTMANAGER_H_
#define CROSSENGINE_INPUTMANAGER_H_

#include <glm/glm.hpp>
#include <unordered_map>
#include "../entry/input.h"

namespace CrossEngine {
/**
 * @brief Input manager stores a key map that maps SDL_Keys to booleans.
 * If the value in the key map is true, then the key is pressed.
 * Otherwise, it is released.
 */
class InputManager {
 public:
  /**
   * @brief Copy constructor.
   * Deleted.
   */
  InputManager(InputManager const&) = delete;

  /**
   * @brief Move constructor.
   * Deleted.
   */
  InputManager(InputManager&&) = delete;

  /**
   * @brief Copy assign.
   * Deleted.
   *
   * @return InputManager& Nothing.
   */
  InputManager& operator=(InputManager const&) = delete;

  /**
   * @brief Move assign.
   * Deleted.
   *
   * @return InputManager& Nothing.
   */
  InputManager& operator=(InputManager&&) = delete;

  /**
   * @brief Instanciate the singleton.
   *
   * @return InputManager& The input manager singleton.
   */
  static InputManager& instance() {
    static InputManager* instance = new InputManager();
    return *instance;
  }

  /**
   * @brief Update the state of the inputs.
   */
  void Update();

  /**
   * @brief Press the key.
   *
   * @param[in] key_id The key.
   */
  void PressKey(entry::Key::Enum key_id);

  /**
   * @brief Release the key.
   *
   * @param[in] key_id The key.
   */
  void ReleaseKey(entry::Key::Enum key_id);

  /**
   * @brief Set the mouse coordinates.
   *
   * @param[in] x The X axis.
   * @param[in] y The Y axis.
   */
  void SetMouseCoords(float x, float y);

  /**
   * @brief Check if the key is pressed.
   *
   * @param[in] key_id The key.
   * @return true If the key is pressed.
   * @return false If the key is release.
   */
  bool IsKeyDown(entry::Key::Enum key_id);

  /**
   * @brief Check if the key is pressed.
   *
   * @param[in] key_id The key.
   * @return true If the key is pressed.
   * @return false If the key is release.
   */
  // bool IsKeyDown(entry::Key::Enum key_id);

  /**
   * @brief Check if the key is down.
   *
   * @param[in] key_id The key.
   * @return true If the key is down.
   * @return false If the key is down.
   */
  bool IsKeyPressed(entry::Key::Enum key_id);

  /**
   * @brief Get the mouse coordinates.
   *
   * @return glm::vec2 The coordinates.
   */
  glm::vec2 GetMouseCoords() const { return mouse_coords_; }

  /**
   * @brief Get the mouse state.
   *
   * @return entry::MouseState The mouse state.
   */
  entry::MouseState* GetMouseState() { return &mouse_state_; }

 private:
  /**
   * @brief Construct a new InputManager object.
   */
  InputManager();

  /**
   * @brief Destroy the InputManager object.
   */
  ~InputManager();

  /**
   * @brief Check the past state of the key.
   *
   * @param[in] keyID The key.
   * @return true If the key was down.
   * @return false If the key was not down.
   */
  bool WasKeyDown(entry::Key::Enum key_id);

  std::unordered_map<entry::Key::Enum, bool> key_map_;
  std::unordered_map<entry::Key::Enum, bool> previous_key_map_;
  glm::vec2 mouse_coords_;
  entry::MouseState mouse_state_;

  static InputManager* instance_;
};
}  // namespace CrossEngine

#endif  // CROSSENGINE_INPUTMANAGER_H_
