/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_WINDOW_H_
#define CROSSENGINE_WINDOW_H_

#include <SDL/SDL.h>
#include <string>

namespace CrossEngine {
/**
 * @brief The windows flags.
 */
enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

class Window {
 public:
  /**
   * @brief Construct a new Window object.
   */
  Window();

  /**
   * @brief Destroy the Window object.
   *
   */
  ~Window();

  /**
   * @brief Creates a windows.
   *
   * @param[in] window_name The name of the window.
   * @param[in] screen_width The width of the window.
   * @param[in] screen_height The height of the window.
   * @param[in] current_flags The flags of the window.
   * @return int 0 successfully create the windows, otherwise an error code.
   */
  int Create(std::string window_name, int screen_width, int screen_height,
             unsigned int current_flags);

  /**
   * @brief Swap the buffer to render the image to the screen.
   */
  void SwapBuffer();

  /**
   * @brief Get the width of the screen.
   *
   * @return int The width.
   */
  int GetScreenWidth() { return screen_width_; }

  /**
   * @brief Get the height of the screen.
   *
   * @return int The height.
   */
  int GetScreenHeight() { return screen_height_; }

  /**
   * @brief Set the name of the window.
   *
   * @deprecated since 0.0.0.2.3
   * @param[in] name The new name of the window.
   */
  void SetWindowName(const char* name) {
    // SDL_SetWindowTitle(m_sdlWindow, name);
  }

  /**
   * @brief Set the Window Size object.
   *
   * @param[in] width The new window width.
   * @param[in] height The new window height.
   */
  void SetWindowSize(int width, int height);

 private:
  SDL_Window* sdl_window_;
  int screen_width_, screen_height_;
};
}  // namespace CrossEngine

#endif  // CROSSENGINE_WINDOW_H_
