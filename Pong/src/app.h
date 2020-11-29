/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef PONG_SRC_APP_H_
#define PONG_SRC_APP_H_

#include <crossengine/i_main_game.h>

#include <memory>

#include "gameplay_screen.h"

/**
 * @brief Our custom app that inherits from IMainGame.
 */
class App : public CrossEngine::IMainGame {
 public:
  /**
   * @brief Construct a new App object.
   */
  App();

  /**
   * @brief Destroy the App object.
   */
  ~App();

  /**
   * @brief Called on initialization.
   */
  void OnInit() override;

  /**
   * @brief For adding all screens.
   */
  void AddScreens() override;

  /**
   * @brief Called when exiting.
   */
  void OnExit() override;

 private:
  std::unique_ptr<GameplayScreen> gameplay_screen_;

  CrossEngine::Window window_;
};

#endif  // PONG_SRC_APP_H_
