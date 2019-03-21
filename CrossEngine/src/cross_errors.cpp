/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "crossengine/cross_errors.h"

#include <SDL/SDL.h>
#include <cstdlib>
#include <iostream>
#include <string>

namespace CrossEngine {
/// Prints out an error message and exits the game
void FatalError(std::string error_string) {
  std::cout << error_string << std::endl;
  std::cout << "Enter any key to quit...";
  int tmp;
  std::cin >> tmp;
  SDL_Quit();
  exit(69);
}
}  // namespace CrossEngine
