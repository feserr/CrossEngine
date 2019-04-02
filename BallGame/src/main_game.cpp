/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "main_game.h"

#include <SDL/SDL.h>
#include <crossengine/cpp_utils.h>
#include <crossengine/cross_engine.h>
#include <crossengine/input_manager.h>
#include <crossengine/resource_manager.h>
#include <entry/input.h>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include "screen_indexs.h"

// Some helpful constants.
const float DESIRED_FPS = 60.0f;   // FPS the game is designed to run at
const int MAX_PHYSICS_STEPS = 6;   // Max number of physics steps per frame
const float MS_PER_SECOND = 1000;  // Number of milliseconds in a second
const float DESIRED_FRAMETIME =
    MS_PER_SECOND / DESIRED_FPS;    // The desired frame time per frame
const float MAX_DELTA_TIME = 1.0f;  // Maximum size of deltaTime

MainGame::MainGame(CrossEngine::Window* window) : window_(*window) {
  screen_index_ = SCREEN_INDEX_GAMEPLAY;
}

MainGame::~MainGame() {
  // Empty
  for (int i = 0; i < ball_renderers_.size(); i++) {
    delete ball_renderers_[i];
  }
}

int MainGame::GetNextScreenIndex() const { return SCREEN_INDEX_GAMEPLAY; }

int MainGame::GetPreviousScreenIndex() const { return SCREEN_INDEX_MAINMENU; }

void MainGame::Build() {}

void MainGame::Destroy() {
  // Cleanup.
}

void MainGame::Update() {
  if (game_state_ == GameState::EXIT) {
    SetState(CrossEngine::ScreenState::EXIT_APPLICATION);
  }

  // Start our previousTicks variable
  static Uint32 previousTicks = SDL_GetTicks();

  // Game loop
  ProcessInput();

  // Calculate the frameTime in milliseconds
  Uint32 newTicks = SDL_GetTicks();
  Uint32 frameTime = newTicks - previousTicks;
  previousTicks =
      newTicks;  // Store newTicks in previousTicks so we can use it next frame
  // Get the total delta time
  float totalDeltaTime = static_cast<float>(frameTime) / DESIRED_FRAMETIME;

  int i = 0;  // This counter makes sure we don't spiral to death!
  // Loop while we still have steps to process.
  while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS) {
    // The deltaTime should be the the smaller of the totalDeltaTime and
    // MAX_DELTA_TIME
    float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
    // Update all physics here and pass in deltaTime

    Update(deltaTime);

    // Since we just took a step that is length deltaTime, subtract from
    // totalDeltaTime
    totalDeltaTime -= deltaTime;
    // Increment our frame counter so we can limit steps to MAX_PHYSICS_STEPS
    i++;
  }

  camera_.Update();
}

void MainGame::OnEntry() {
  screen_width_ = 1280;
  screen_height_ = 720;

  // Init camera
  camera_.Init(window_.screen_width, window_.screen_height);
  camera_.SetPosition(glm::vec2(0.0f));
  camera_.SetScale(1.0f);

  sprite_batch_.Init();

  fps_limiter_.SetMaxFPS(60.0f);

  InitRenderers();
  InitBalls();
}

void MainGame::OnExit() {}

void MainGame::InitRenderers() { ball_renderers_.push_back(new BallRenderer); }

struct BallSpawn {
  BallSpawn(const CrossEngine::ColorRGBA8& colr, float rad, float m,
            float minSpeed, float maxSpeed, float prob)
      : color(colr),
        radius(rad),
        mass(m),
        randSpeed(minSpeed, maxSpeed),
        probability(prob) {
    // Empty
  }
  CrossEngine::ColorRGBA8 color;
  float radius;
  float mass;
  float probability;
  std::uniform_real_distribution<float> randSpeed;
};

void MainGame::InitBalls() {
  // Initialize the grid
  grid_ = std::make_unique<Grid>(screen_width_, screen_height_, CELL_SIZE);

#define ADD_BALL(p, ...) \
  totalProbability += p; \
  possibleBalls.emplace_back(__VA_ARGS__);

  // Number of balls to spawn
  const int NUM_BALLS = 10000;

  // Random engine stuff
  std::mt19937 randomEngine(static_cast<unsigned int>(time(nullptr)));
  std::uniform_real_distribution<float> randX(
      0.0f, static_cast<float>(screen_width_));
  std::uniform_real_distribution<float> randY(
      0.0f, static_cast<float>(screen_height_));
  std::uniform_real_distribution<float> randDir(-1.0f, 1.0f);

  // Add all possible balls
  std::vector<BallSpawn> possibleBalls;
  float totalProbability = 0.0f;

  /// Random values for ball types
  std::uniform_real_distribution<float> r1(2.0f, 6.0f);
  std::uniform_int_distribution<int> r2(0, 255);

  // Adds the balls using a macro
  ADD_BALL(1.0f, CrossEngine::ColorRGBA8(255, 255, 255, 255), 2.0f, 1.0f, 0.1f,
           7.0f, totalProbability);
  ADD_BALL(1.0f, CrossEngine::ColorRGBA8(1, 254, 145, 255), 2.0f, 2.0f, 0.1f,
           3.0f, totalProbability);
  ADD_BALL(1.0f, CrossEngine::ColorRGBA8(177, 0, 254, 255), 3.0f, 4.0f, 0.0f,
           0.0f, totalProbability)
  ADD_BALL(1.0f, CrossEngine::ColorRGBA8(254, 0, 0, 255), 3.0f, 4.0f, 0.0f,
           0.0f, totalProbability);
  ADD_BALL(1.0f, CrossEngine::ColorRGBA8(0, 255, 255, 255), 3.0f, 4.0f, 0.0f,
           0.0f, totalProbability);
  ADD_BALL(1.0f, CrossEngine::ColorRGBA8(255, 255, 0, 255), 3.0f, 4.0f, 0.0f,
           0.0f, totalProbability);
  // Make a bunch of random ball types
  for (int i = 0; i < 10000; i++) {
    ADD_BALL(1.0f,
             CrossEngine::ColorRGBA8(r2(randomEngine), r2(randomEngine),
                                     r2(randomEngine), 255),
             r1(randomEngine), r1(randomEngine), 0.0f, 0.0f, totalProbability);
  }

  // Random probability for ball spawn
  std::uniform_real_distribution<float> spawn(0.0f, totalProbability);

  // Small optimization that sets the size of the internal array to prevent
  // extra allocations.
  balls_.reserve(NUM_BALLS);

  // Set up ball to spawn with default value
  BallSpawn* ballToSpawn = &possibleBalls[0];
  for (int i = 0; i < NUM_BALLS; i++) {
    // Get the ball spawn roll
    float spawnVal = spawn(randomEngine);
    // Figure out which ball we picked
    for (size_t j = 0; j < possibleBalls.size(); j++) {
      if (spawnVal <= possibleBalls[j].probability) {
        ballToSpawn = &possibleBalls[j];
        break;
      }
    }

    // Get random starting position
    glm::vec2 pos(randX(randomEngine), randY(randomEngine));

    // Hacky way to get a random direction
    glm::vec2 direction(randDir(randomEngine), randDir(randomEngine));
    if (direction.x != 0.0f ||
        direction.y !=
            0.0f) {  // The chances of direction == 0 are astronomically low
      direction = glm::normalize(direction);
    } else {
      direction = glm::vec2(1.0f, 0.0f);  // default direction
    }

    // Add ball
    balls_.emplace_back(
        ballToSpawn->radius, ballToSpawn->mass, pos,
        direction * ballToSpawn->randSpeed(randomEngine),
        CrossEngine::ResourceManager::GetTexture("images/circle.png"),
        ballToSpawn->color);
    // Add the ball do the grid. IF YOU EVER CALL EMPLACE BACK AFTER INIT BALLS,
    // grid_ will have DANGLING POINTERS!
    grid_->AddBall(&balls_.back());
  }
}

void MainGame::Update(const float deltaTime) {
  ball_controller_.UpdateBalls(&balls_, grid_.get(), deltaTime, screen_width_,
                               screen_height_);
}

void MainGame::Draw() {
  camera_.Draw();

  // Grab the camera matrix
  glm::mat4 projectionMatrix = camera_.GetCameraMatrix();

  ball_renderers_[current_renderer_]->RenderBalls(sprite_batch_, balls_,
                                                  projectionMatrix);

  DrawHud();

  // m_textureProgram.Unuse();

  // window_.SwapBuffer();
}

void MainGame::DrawHud() {
  const CrossEngine::ColorRGBA8 fontColor(255, 0, 0, 255);
  // Convert float to char *
  char buffer[64];
  snprintf(buffer, sizeof(buffer), "%.1f", fps_);

  sprite_batch_.Begin();
  // m_spriteFont->Draw(sprite_batch_, buffer, glm::vec2(5.0f, screen_height_
  // - 64.0f),
  // glm::vec2(1.0f), 0.0f, fontColor);
  sprite_batch_.End();
  sprite_batch_.RenderBatch();
}

void MainGame::ProcessInput() {
  if (CrossEngine::InputManager::instance().IsKeyDown(entry::Key::Esc)) {
    game_state_ = GameState::EXIT;
  }
  // Handle gravity changes
  if (CrossEngine::InputManager::instance().IsKeyDown(entry::Key::Left)) {
    ball_controller_.SetGravityDirection(GravityDirection::LEFT);
  } else if (CrossEngine::InputManager::instance().IsKeyDown(
                 entry::Key::Right)) {
    ball_controller_.SetGravityDirection(GravityDirection::RIGHT);
  } else if (CrossEngine::InputManager::instance().IsKeyDown(entry::Key::Up)) {
    ball_controller_.SetGravityDirection(GravityDirection::DOWN);
  } else if (CrossEngine::InputManager::instance().IsKeyDown(
                 entry::Key::Down)) {
    ball_controller_.SetGravityDirection(GravityDirection::UP);
  } else if (CrossEngine::InputManager::instance().IsKeyDown(
                 entry::Key::Space)) {
    ball_controller_.SetGravityDirection(GravityDirection::NONE);
  }

  entry::MouseState mouse_state =
      *CrossEngine::InputManager::instance().GetMouseState();
  ball_controller_.OnMouseMove(&balls_, static_cast<float>(mouse_state.m_mx),
                               static_cast<float>(mouse_state.m_my));

  if (!!mouse_state.m_buttons[entry::MouseButton::Left]) {
    ball_controller_.OnMouseDown(&balls_, static_cast<float>(mouse_state.m_mx),
                                 static_cast<float>(mouse_state.m_my));
  } else {
    ball_controller_.OnMouseUp(&balls_);
  }

  // Switch renderers
  if (CrossEngine::InputManager::instance().IsKeyDown(entry::Key::Key1)) {
    current_renderer_++;
    if (current_renderer_ >= ball_renderers_.size()) {
      current_renderer_ = 0;
    }
  }
}
