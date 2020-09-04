/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_I_GAME_SCREEN_H_
#define CROSSENGINE_I_GAME_SCREEN_H_

const int SCREEN_INDEX_NO_SCREEN = -1;

namespace CrossEngine {
class IMainGame;

enum ScreenState {
  NONE = 0,
  RUNNING = 1,
  EXIT_APPLICATION = 2,
  CHANGE_NEXT = 3,
  CHANGE_PREVIOUS = 4
};

/**
 * @brief Game screen interface.
 */
class IGameScreen {
 public:
  friend class ScreenList;

  /**
   * @brief Construct a new IGameScreen object.
   */
  IGameScreen() {}

  /**
   * @brief Destroy the IGameScreen object.
   */
  virtual ~IGameScreen() {}

  /**
   * @brief Gets the next screen index.
   *
   * @return The next screen index.
   */
  virtual int GetNextScreenIndex() const = 0;

  /**
   * @brief Gets the previous screen index.
   *
   * @return The previous screen index.
   */
  virtual int GetPreviousScreenIndex() const = 0;

  /**
   * @brief Builds the game.
   */
  virtual void Build() = 0;

  /**
   * @brief Destroy the game.
   */
  virtual void Destroy() = 0;

  /**
   * @brief Called when a screen enters focus.
   */
  virtual void OnEntry() = 0;

  /**
   * @brief Called when a screen exits focus.
   */
  virtual void OnExit() = 0;

  /**
   * @brief Updates the game screen.
   */
  virtual void Update() = 0;

  /**
   * @brief Draw the game screen.
   */
  virtual void Draw() = 0;

  /**
   * @brief Gets the screen index.
   *
   * @return The screen index.
   */
  int GetScreenIndex() const { return screen_index_; }

  /**
   * @brief Sets the game in running state.
   */
  void SetRunning() { current_state_ = ScreenState::RUNNING; }

  /**
   * @brief Gets the state.
   *
   * @return The state.
   */
  ScreenState GetState() const { return current_state_; }

  /**
   * @brief Set the state.
   *
   * @param[in] state The new state.
   */
  void SetState(ScreenState state) { current_state_ = state; }

  /**
   * @brief Sets the parent game.
   *
   * @param[in] game The game.
   */
  void SetParentGame(IMainGame* game) { game_ = game; }

 protected:
  ScreenState current_state_ = ScreenState::NONE;
  IMainGame* game_ = nullptr;
  int screen_index_ = -1;
};
}  // namespace CrossEngine

#endif  // CROSSENGINE_I_GAME_SCREEN_H_
