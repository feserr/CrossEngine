/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "gameplay_screen.h"

#include <SDL/SDL.h>
#include <crossengine/i_main_game.h>
#include <crossengine/resource_manager.h>
#include <algorithm>
#include <iostream>
#include <random>
#include "screen_indexs.h"

const float kDesiredFps = 60.0f;  // FPS the game is designed to run at
const int kMaxPhysicsSteps = 6;   // Max number of physics steps per frame
const float kMsPerSecond = 1000;  // Number of milliseconds in a second
const float kDesiredFrametime =
    kMsPerSecond / kDesiredFps;    // The desired frame time per frame
const float kMaxDeltaTime = 1.0f;  // Maximum size of deltaTime

GameplayScreen::GameplayScreen(CrossEngine::Window* window)
    : window_(window), score_player_one_(0), score_player_two_(0) {
  screen_index_ = SCREEN_INDEX_GAMEPLAY;
}

GameplayScreen::~GameplayScreen() {}

int GameplayScreen::GetNextScreenIndex() const { return SCREEN_INDEX_MAINMENU; }

int GameplayScreen::GetPreviousScreenIndex() const {
  return SCREEN_INDEX_MAINMENU;
}

void GameplayScreen::Build() {}

void GameplayScreen::Destroy() {
  // Cleanup.
}

void GameplayScreen::OnEntry() {
  // Initialize spritebatch
  sprite_batch_.Init();

  // Init camera
  camera_.Init(window_->screen_width, window_->screen_height);
  camera_.SetPosition(glm::vec2(0.0f));
  camera_.SetScale(1.0f);

  // Init players
  glm::vec2 position(32.0f, window_->screen_height / 2);
  glm::vec2 draw_dims(32.0f, 32.0f);
  glm::vec2 collision_dims(32.0f, 48.0f);
  player_one_.Init(position, draw_dims, collision_dims,
                   CrossEngine::ColorRGBA8(255, 255, 255, 255),
                   PlayerType::PLAYERONE);

  position = glm::vec2(window_->screen_width - 32.0f,
                       window_->screen_height / 2);
  player_two_.Init(position, draw_dims, collision_dims,
                   CrossEngine::ColorRGBA8(255, 255, 255, 255),
                   PlayerType::PLAYERTWO);

  // Init the ball
  position = glm::vec2(window_->screen_width / 2,
                       window_->screen_height / 2);
  glm::vec2 vel(-6.0f, 0.0f);
  ball_.Init(position, vel,8.0f, 0.0f);

  // Init the environment
  position = glm::vec2(window_->screen_width / 2, 0.0f);
  for (int i = 16; i <= window_->screen_height; i += 64) {
    Environment environment;
    position.y = i;
    environment.Init(position, draw_dims,
                     CrossEngine::ColorRGBA8(255, 255, 255, 130));
    enviroment_.push_back(environment);
  }

  window_size_ =
      glm::vec2(window_->screen_width, window_->screen_height);
}

void GameplayScreen::OnExit() {}

void GameplayScreen::Update() {
  CheckInput();
  
  if (game_state_ == GameState::EXIT) {
    SetState(CrossEngine::ScreenState::EXIT_APPLICATION);
  }

  // Calculate the frameTime in milliseconds
  static Uint32 previousTicks = SDL_GetTicks();
  Uint32 newTicks = SDL_GetTicks();
  Uint32 frameTime = newTicks - previousTicks;
  previousTicks = newTicks;
  // Get the total delta time
  float total_delta_time = static_cast<float>(frameTime / kDesiredFrametime);

  int i = 0;
  int goal = 0;
  while (total_delta_time > 0.0f && i < kMaxPhysicsSteps) {
    // The deltaTime should be the the smaller of the total_delta_time and
    // MAX_DELTA_TIME
    float deltaTime = std::min(total_delta_time, kMaxDeltaTime);
    // Update all physics here and pass in deltaTime

    int t_goal = ball_.Update(deltaTime, window_size_);
    player_one_.Update(deltaTime, window_size_, &ball_);
    player_two_.Update(deltaTime, window_size_, &ball_);

    // Since we just took a step that is length deltaTime, subtract from
    // total_delta_time
    total_delta_time -= deltaTime;
    ++i;

    // Prevent scoring more than one goal
    if (goal == 0) {
      goal = t_goal;
    }
  }

  if (goal == 1) {
    ++score_player_two_;
    // m_scorePlayerTwo->setText(std::to_string(m_iScorePlayerTwo));
  } else if (goal == 2) {
    ++score_player_one_;
    // m_scorePlayerOne->setText(std::to_string(m_iScorePlayerOne));
  }

  glm::vec2 cp = camera_.GetPosition();
  cp.x--;
  camera_.SetPosition(cp);
  camera_.Update();
}

void GameplayScreen::Draw() {
  camera_.Draw();

  sprite_batch_.Begin();

  player_one_.Draw(&sprite_batch_);
  player_two_.Draw(&sprite_batch_);
  ball_.Draw(&sprite_batch_);

  for (Environment environment : enviroment_) {
    environment.Draw(&sprite_batch_);
  }

  sprite_batch_.End();
  sprite_batch_.RenderBatch();
}

void GameplayScreen::InitUI() {
  // Init the UI
}

void GameplayScreen::CheckInput() {
  if (CrossEngine::InputManager::instance().IsKeyDown(entry::Key::Esc)) {
    game_state_ = GameState::EXIT;
  }
}

bool GameplayScreen::OnExitClicked() {
  SetState(CrossEngine::ScreenState::EXIT_APPLICATION);
  current_state_ = CrossEngine::ScreenState::EXIT_APPLICATION;
  return true;
}
