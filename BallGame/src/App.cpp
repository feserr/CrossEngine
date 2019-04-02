/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "app.h"

#include <crossengine/cpp_utils.h>
#include <crossengine/screen_list.h>

#if __cplusplus > 199711L
#else
#include <memory>
#endif

App::App() : gameplay_screen_(nullptr) {}

App::~App() {}

void App::OnInit() {
  window_.screen_width = 1280;
  window_.screen_height = 720;
}

void App::AddScreens() {
  gameplay_screen_ = std::make_unique<MainGame>(&window_);
  screen_list_->AddScreen(gameplay_screen_.get());
  screen_list_->SetScreen(gameplay_screen_->GetScreenIndex());
}

void App::OnExit() {}
