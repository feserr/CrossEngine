
#include "App.h"

#include <CrossEngine/IMainGame.h>
#include <common.h>
#include <bgfx_utils.h>

int _main_(int _argc, char** _argv) {
    App app;
    app.Run(_argc, _argv);
    return 0;
}