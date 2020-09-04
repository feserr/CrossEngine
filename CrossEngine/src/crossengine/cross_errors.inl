/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include <SDL/SDL.h>

#include <iostream>
#include <string>

namespace CrossEngine {
inline void FatalError(const std::string &error_string) {
  std::cout << error_string << std::endl;
  std::cout << "Enter any key to quit...";
  int tmp;
  std::cin >> tmp;
  SDL_Quit();
  exit(123);
}
}  // namespace CrossEngine
