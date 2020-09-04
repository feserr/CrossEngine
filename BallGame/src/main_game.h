/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef BALLGAME_SRC_MAIN_GAME_H_
#define BALLGAME_SRC_MAIN_GAME_H_

#include <crossengine/camera.h>
#include <crossengine/i_game_screen.h>
#include <crossengine/sprite_batch.h>
#include <crossengine/timing.h>
#include <crossengine/window.h>

#include <memory>
#include <vector>

#include "../src/ball_controller.h"
#include "../src/ball_renderer.h"
#include "../src/grid.h"

struct ViewState {
  ViewState(uint32_t _width = 0, uint32_t _height = 0)
      : m_width(_width), m_height(_height) {}

  uint32_t m_width;
  uint32_t m_height;

  float m_view[16];
  float m_proj[16];
};

enum class GameState { RUNNING, EXIT };

const int CELL_SIZE = 12;

class MainGame : public CrossEngine::IGameScreen {
 public:
  /**
   * @brief Construct a new MainGame object.
   *
   * @param window The windows object used for the app.
   */
  explicit MainGame(CrossEngine::Window* window);

  /**
   * @brief Destroy the MainGame object.
   */
  ~MainGame();

  /**
   * @brief Get the next screen index.
   *
   * @return int The screen index.
   */
  int GetNextScreenIndex() const override;

  /**
   * @brief Get the previous screen index.
   *
   * @return int The screen index.
   */
  int GetPreviousScreenIndex() const override;

  /**
   * @brief Build the game.
   */
  void Build() override;

  /**
   * @brief Destroy the game.
   */
  void Destroy() override;

  /**
   * @brief On entry callback.
   */
  void OnEntry() override;

  /**
   * @brief On exit callback.
   */
  void OnExit() override;

  /**
   * @brief Main game loop.
   */
  void Update() override;

  /**
   * @brief Main game draw loop.
   */
  void Draw() override;

 private:
  void Init();
  void InitRenderers();
  void InitBalls();
  void Update(const float delta_time);
  void DrawHud();
  void ProcessInput();

  int screen_width_ = 0;
  int screen_height_ = 0;

  std::vector<Ball> balls_;     ///< All the balls
  std::unique_ptr<Grid> grid_;  ///< Grid for spatial partitioning for collision

  uint32_t current_renderer_ = 0;
  std::vector<BallRenderer*> ball_renderers_;

  BallController ball_controller_;  ///< Controls balls

  CrossEngine::Window window_;             ///< The main window
  CrossEngine::SpriteBatch sprite_batch_;  ///< Renders all the balls

  ViewState viewState_;

  GameState game_state_ = GameState::RUNNING;  ///< The state of the game
};

#endif  // BALLGAME_SRC_MAIN_GAME_H_
