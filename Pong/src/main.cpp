/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include <crossengine/bgfx_utils.h>
#include <crossengine/common.h>
#include <crossengine/i_main_game.h>

#include "app.h"

int _main_(int _argc, char** _argv) {
  App app;
  app.Run(_argc, _argv);
  return 0;
}
