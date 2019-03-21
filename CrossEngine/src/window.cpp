/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "crossengine/window.h"

#include <string>
#include "crossengine/cross_errors.h"

namespace CrossEngine {
Window::Window() {}

Window::~Window() {}

int Window::Create(std::string window_name, int screen_width, int screen_height,
                   unsigned int current_flags) {
  Uint32 flags = SDL_WINDOW_OPENGL;
  screen_width_ = screen_width;
  screen_height_ = screen_height;

  if (current_flags & INVISIBLE) {
    flags |= SDL_WINDOW_HIDDEN;
  }
  if (current_flags & FULLSCREEN) {
    flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
  }
  if (current_flags & BORDERLESS) {
    flags |= SDL_WINDOW_BORDERLESS;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // Open an SDL window
  sdl_window_ = SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, screen_width_,
                                 screen_height, flags);
  if (sdl_window_ == nullptr) {
    FatalError("SDL Window could not be created!");
  }

  // Set up our OpenGL context
  SDL_GLContext glContext = SDL_GL_CreateContext(sdl_window_);
  if (glContext == nullptr) {
    FatalError("SDL_GL context could not be created!");
  }

  // Init glew for OSX systems
  /*
#if __APPLE__
  glewExperimental = GL_TRUE;
  glewInit();
#endif
  */

  // printf("***  Supported GLSL version is %s  ***\n",
  //    reinterpret_cast<char*>(const_cast<GLubyte*>(
  //        glGetString(GL_SHADING_LANGUAGE_VERSION))));

  // Set the background color to blue
  // glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

  // Set VSYNC
  SDL_GL_SetSwapInterval(0);

  // Enable alpha blend
  // glEnable(GL_BLEND);
  // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  return 0;
}

void Window::SwapBuffer() { SDL_GL_SwapWindow(sdl_window_); }

void Window::SetWindowSize(int width, int height) {
  screen_width_ = width;
  screen_height_ = height;
  // SDL_SetWindowSize(m_sdlWindow, m_screen_width_, m_screen_height);
}
}  // namespace CrossEngine
