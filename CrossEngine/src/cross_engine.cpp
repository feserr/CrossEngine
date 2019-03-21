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

  // Tell SDL that we want a double buffered window so we dont get
  // any flickering
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  return 0;
}
}  // namespace CrossEngine
