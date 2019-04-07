/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_I_MAIN_GAME_H_
#define CROSSENGINE_I_MAIN_GAME_H_

#include <memory>
#include "cross_engine.h"
#include "timing.h"
#include "window.h"

namespace CrossEngine {
class ScreenList;
class IGameScreen;

/**
 * @brief Main game interface.
 */
class IMainGame {
 public:
  /**
   * @brief Construct a new IMainGame object.
   */
  IMainGame();

  /**
   * @brief Destroy the IMainGame object.
   */
  virtual ~IMainGame();

  /**
   * @brief Runs and initializes the game.
   *
   * @param[in] _argc The number of arguments.
   * @param[in] _argv The arguments.
   */
  void Run(int _argc, char** _argv);

  /**
   * @brief Exits the game.
   *
   * @return int 0 if exit correctly, otherwise an error code.
   */
  virtual int ExitGame();

  /**
   * @brief Called on initialization.
   */
  virtual void OnInit() = 0;

  /**
   * @brief For adding all screens.
   */
  virtual void AddScreens() = 0;

  /**
   * @brief Called when exiting.
   */
  virtual void OnExit() = 0;

  /**
   * @brief Gets the FPS.
   *
   * @return The FPS.
   */
  const float GetFps() const { return fps_; }

 protected:
  /**
   * @brief Custom update function.
   */
  virtual void Update();

  /**
   * @brief Custom render function
   */
  virtual void Draw();

  /**
   * @brief Initialize the main game.
   *
   * @param[in] _argc The number of arguments.
   * @param[on] _argv The arguments.
   * @return true if it initialize correctly.
   * @return false If fail to initialize.
   */
  bool Init(int _argc, char** _argv);

  /**
   * @brief
   *
   * @param[in] _argc The number of arguments.
   * @param[on] _argv The arguments.
   * @return true if it initialize the systems correctly.
   * @return false If fail to initialize the systems.
   */
  bool InitSystems(int _argc, char** _argv);

  std::unique_ptr<ScreenList> screen_list_;
  IGameScreen* current_screen_ = nullptr;
  bool is_running_ = false;
  float fps_ = 0.0f;

 private:
  // Window window_;
  uint32_t width_;
  uint32_t height_;
  uint32_t debug_;
  uint32_t reset_;
};
}  // namespace CrossEngine

#endif  // CROSSENGINE_I_MAIN_GAME_H_
