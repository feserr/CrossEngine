/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include <CrossEngine/i_main_game.h>
#include <CrossEngine/bgfx_utils.h>
#include <CrossEngine/common.h>
#include "App.h"

int _main_(int _argc, char** _argv) {
  App app;
  app.Run(_argc, _argv);
  return 0;
}
