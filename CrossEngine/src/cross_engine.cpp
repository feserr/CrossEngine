/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "crossengine/cross_engine.h"

#include <SDL/SDL.h>

namespace CrossEngine {
int Init() {
  // Initialize SDL
  SDL_Init(SDL_INIT_EVERYTHING);

  return 0;
}
}  // namespace CrossEngine
