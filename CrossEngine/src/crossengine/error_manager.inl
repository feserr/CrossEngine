/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include <SDL/SDL.h>

#include <iostream>
#include <stdexcept>
#include <string>

namespace CrossEngine {
inline void FatalError(const std::string &error_string) {
  SDL_Quit();
  throw std::runtime_error(error_string);
}
}  // namespace CrossEngine
