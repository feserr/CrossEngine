/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_WINDOW_H_
#define CROSSENGINE_WINDOW_H_

#include <SDL/SDL.h>
#include <string>

namespace CrossEngine {
/**
 * @brief The windows flags.
 */
enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

struct Window {
  int screen_width, screen_height;
};
}  // namespace CrossEngine

#endif  // CROSSENGINE_WINDOW_H_
