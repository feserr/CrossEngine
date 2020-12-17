/*
 * Copyright 2020 Javier Jorge. All rights reserved.
 * License: https://github.com/JJorgeDSIC/CppDecoder#license
 */

#include <crossengine/common.h>
#include <crossengine/cpp_utils.h>
#include <crossengine/i_game_screen.h>
#include <crossengine/i_main_game.h>
#include <crossengine/screen_list.h>

#include <stdexcept>
#include <vector>

#include "gtest/gtest.h"

class MainGame : public CrossEngine::IGameScreen {
 public:
  explicit MainGame(CrossEngine::Window* window) {}
  ~MainGame() {}

  int GetNextScreenIndex() const override { return 0; }
  int GetPreviousScreenIndex() const override { return 0; }

  void Build() override {}
  void Destroy() override {}
  void OnEntry() override {}
  void OnExit() override {}
  void Update() override {}
  void Draw() override {}
};

class App : public CrossEngine::IMainGame {
 public:
  App() : gameplay_screen_(nullptr) {}
  ~App() {}

  void OnInit() override {
    window_.screen_width = 1280;
    window_.screen_height = 720;
  }

  void AddScreens() override {
    gameplay_screen_ = CrossEngine::make_unique<MainGame>(&window_);
    screen_list_->AddScreen(gameplay_screen_.get());
    screen_list_->SetScreen(gameplay_screen_->GetScreenIndex());
    ExitGame();
  }

  void OnExit() override {}

  std::unique_ptr<MainGame> gameplay_screen_;
  CrossEngine::Window window_;
};

TEST(Init, CrossEngineTest) {
  char* argv = reinterpret_cast<char*>(malloc(1));
  App app;
  app.Run(0, &argv);
  free(argv);
}

int _main_(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
