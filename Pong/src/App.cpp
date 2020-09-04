/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "app.h"

#include <crossengine/cpp_utils.h>
#include <crossengine/screen_list.h>

App::App() {}

App::~App() {}

void App::OnInit() {
  window_.screen_width = 640;
  window_.screen_height = 480;
}

void App::AddScreens() {
  gameplay_screen_ = std::make_unique<GameplayScreen>(&window_);

  screen_list_->AddScreen(gameplay_screen_.get());
  screen_list_->SetScreen(gameplay_screen_->GetScreenIndex());
}

void App::OnExit() {}
