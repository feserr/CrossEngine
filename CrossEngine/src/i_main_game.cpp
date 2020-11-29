/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "crossengine/i_main_game.h"

#include <SDL/SDL_syswm.h>
#include <bgfx/bgfx.h>

#include <memory>

#include "crossengine/cpp_utils.h"
#include "crossengine/i_game_screen.h"
#include "crossengine/input_manager.h"
#include "crossengine/screen_list.h"
#include "entry/entry.h"

namespace CrossEngine {
IMainGame::IMainGame()
    : current_screen_(nullptr),
      is_running_(false),
      fps_(60.0f),
      width_(640),
      height_(480),
      debug_(0),
      reset_(0) {
  screen_list_ = CrossEngine::make_unique<ScreenList>(this);
}

IMainGame::~IMainGame() {
  // Empty
}

void IMainGame::Run(int _argc, char** _argv) {
  if (!Init(_argc, _argv)) return;

  FpsLimiter limiter;
  limiter.SetMaxFPS(60.0f);

  // Game loop
  is_running_ = true;
  while (is_running_) {
    if (!entry::processEvents(width_, height_, debug_, reset_,
                              InputManager::instance().GetMouseState())) {
      limiter.Begin();

      bgfx::touch(0);

      // Call the custom update and draw method
      Update();
      if (is_running_) {
        Draw();

        fps_ = limiter.End();

        // Advance to next frame. Rendering thread will be kicked to
        // process submitted rendering primitives.
        bgfx::frame();
      }
    } else {
      is_running_ = false;
      bgfx::frame();
      ExitGame();
    }
  }
}

int IMainGame::ExitGame() {
  if (current_screen_) {
    current_screen_->OnExit();
  }

  if (screen_list_) {
    screen_list_->Destroy();
    screen_list_.reset();
  }
  is_running_ = false;

  // Shutdown bgfx.
  bgfx::shutdown();

  return 0;
}

bool IMainGame::Init(int _argc, char** _argv) {
  CrossEngine::Init();

  if (!InitSystems(_argc, _argv)) return false;

  OnInit();
  AddScreens();

  current_screen_ = screen_list_->GetCurrent();
  if (current_screen_) {
    current_screen_->OnEntry();
    current_screen_->SetRunning();
  }

  // Game loop
  is_running_ = true;

  return true;
}

bool IMainGame::InitSystems(int _argc, char** _argv) {
  width_ = 640;
  height_ = 480;
  debug_ = BGFX_DEBUG_TEXT;
  reset_ = BGFX_RESET_VSYNC;

  bgfx::Init init;
  init.type = bgfx::RendererType::Count;
  init.vendorId = BGFX_PCI_ID_NONE;
  init.resolution.width = width_;
  init.resolution.height = height_;
  init.resolution.reset = reset_;
  bgfx::init(init);
  bgfx::reset(width_, height_, reset_);

  // Enable debug text.
  bgfx::setDebug(debug_);

  // Set view 0 clear state.
  bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff);
  bgfx::setViewRect(0, 0, 0, width_, height_);

  return true;
}

void IMainGame::Update() {
  if (current_screen_) {
    switch (current_screen_->GetState()) {
      case ScreenState::RUNNING:
        current_screen_->Update();
        break;
      case ScreenState::CHANGE_NEXT:
        current_screen_->OnExit();
        current_screen_ = screen_list_->MoveNext();
        if (current_screen_) {
          current_screen_->SetRunning();
          current_screen_->OnEntry();
        }
        break;
      case ScreenState::CHANGE_PREVIOUS:
        current_screen_->OnExit();
        current_screen_ = screen_list_->MovePrevious();
        if (current_screen_) {
          current_screen_->SetRunning();
          current_screen_->OnEntry();
        }
        break;
      case ScreenState::EXIT_APPLICATION:
        ExitGame();
        break;
      default:
        break;
    }
  } else {
    ExitGame();
  }
}

void IMainGame::Draw() {
  // This dummy draw call is here to make sure that view 0 is cleared
  // if no other draw calls are submitted to view 0.
  bgfx::touch(0);

  bgfx::dbgTextClear();
  bgfx::dbgTextPrintf(1, 0, 0x0f, "FPS: %.1f", fps_);

  if (current_screen_ && current_screen_->GetState() == ScreenState::RUNNING) {
    current_screen_->Draw();
  }
}
}  // namespace CrossEngine
