/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef PONG_SRC_GAMEPLAY_SCREEN_H_
#define PONG_SRC_GAMEPLAY_SCREEN_H_

#include <crossengine/cross_texture.h>
#include <crossengine/i_game_screen.h>
#include <crossengine/sprite_batch.h>
#include <crossengine/window.h>

#include <vector>

#include "ball.h"
#include "environment.h"
#include "player.h"

const uint16_t textureside = 512;
const uint32_t texture2dSize = 256;

enum class GameState { RUNNING, EXIT };

// Our custom gameplay screen that inherits from the IGameScreen
class GameplayScreen : public CrossEngine::IGameScreen {
 public:
  explicit GameplayScreen(CrossEngine::Window* window);
  ~GameplayScreen() override;

  int GetNextScreenIndex() const override;

  int GetPreviousScreenIndex() const override;

  void Build() override;

  void Destroy() override;

  void OnEntry() override;

  void OnExit() override;

  void Update() override;

  void Draw() override;

 private:
  void InitUI();
  void CheckInput();

  bool OnExitClicked();

  CrossEngine::SpriteBatch sprite_batch_;
  CrossEngine::CrossTexture texture_;
  CrossEngine::Window* window_;

  Player player_one_;
  Player player_two_;
  Ball ball_;
  std::vector<Environment> enviroment_;

  int score_player_one_;
  int score_player_two_;

  glm::vec2 window_size_;

  GameState game_state_ = GameState::RUNNING;  ///< The state of the game
};

#endif  // PONG_SRC_GAMEPLAY_SCREEN_H_
