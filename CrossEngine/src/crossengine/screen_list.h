/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_SCREENLIST_H_
#define CROSSENGINE_SCREENLIST_H_

#include <vector>

namespace CrossEngine {
class IMainGame;
class IGameScreen;

class ScreenList {
 public:
  explicit ScreenList(IMainGame* game);
  ~ScreenList();

  IGameScreen* MoveNext();
  IGameScreen* MovePrevious();

  void SetScreen(int next_screen);
  void AddScreen(IGameScreen* new_screen);

  void Destroy();

  IGameScreen* GetCurrent();

 protected:
  IMainGame* game_ = nullptr;
  std::vector<IGameScreen*> screens_;
  int current_screen_index_ = -1;
};
}  // namespace CrossEngine

#endif  // CROSSENGINE_SCREENLIST_H_
