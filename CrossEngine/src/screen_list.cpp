/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "crossengine/screen_list.h"

#include <cstdio>

#include "crossengine/i_game_screen.h"

namespace CrossEngine {
ScreenList::ScreenList(IMainGame* game)
    : game_(game), screens_(), current_screen_index_(-1) {}

ScreenList::~ScreenList() { Destroy(); }

IGameScreen* CrossEngine::ScreenList::MoveNext() {
  IGameScreen* currentScreen = GetCurrent();
  if (currentScreen->GetNextScreenIndex() != SCREEN_INDEX_NO_SCREEN) {
    current_screen_index_ = currentScreen->GetNextScreenIndex();
  }
  return GetCurrent();
}

IGameScreen* CrossEngine::ScreenList::MovePrevious() {
  IGameScreen* currentScreen = GetCurrent();
  if (currentScreen->GetPreviousScreenIndex() != SCREEN_INDEX_NO_SCREEN) {
    current_screen_index_ = currentScreen->GetPreviousScreenIndex();
  }
  return GetCurrent();
}

void CrossEngine::ScreenList::SetScreen(int next_screen) {
  current_screen_index_ = next_screen;
}

void CrossEngine::ScreenList::AddScreen(IGameScreen* new_screen) {
  new_screen->screen_index_ = static_cast<int>(screens_.size());
  screens_.push_back(new_screen);
  new_screen->Build();
  new_screen->SetParentGame(game_);
}

void CrossEngine::ScreenList::Destroy() {
  for (const auto& screen : screens_) {
    screen->Destroy();
  }
  screens_.resize(0);
  current_screen_index_ = SCREEN_INDEX_NO_SCREEN;
}

IGameScreen* ScreenList::GetCurrent() {
  if (current_screen_index_ == SCREEN_INDEX_NO_SCREEN) return nullptr;
  return screens_[current_screen_index_];
}
}  // namespace CrossEngine
