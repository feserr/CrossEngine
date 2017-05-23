/*
    Copyright [2016] [Elías Serrano]

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "CrossEngine/Window.h"
#include "CrossEngine/CrossErrors.h"

#include <string>

namespace CrossEngine {
    Window::Window() {
    }

    Window::~Window() {
    }

    int Window::Create(std::string windowName, int screenWidth,
        int screenHeight, unsigned int currentFlags) {
        Uint32 flags = SDL_WINDOW_OPENGL;
        m_screenWidth = screenWidth;
        m_screenHeight = screenHeight;

        if (currentFlags & INVISIBLE) {
            flags |= SDL_WINDOW_HIDDEN;
        }
        if (currentFlags & FULLSCREEN) {
            flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        }
        if (currentFlags & BORDERLESS) {
            flags |= SDL_WINDOW_BORDERLESS;
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        // Open an SDL window
        m_sdlWindow = SDL_CreateWindow(windowName.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth,
            screenHeight, flags);
        if (m_sdlWindow == nullptr) {
            FatalError("SDL Window could not be created!");
        }

        // Set up our OpenGL context
        SDL_GLContext glContext = SDL_GL_CreateContext(m_sdlWindow);
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
        
        //printf("***  Supported GLSL version is %s  ***\n",
        //    reinterpret_cast<char*>(const_cast<GLubyte*>(
        //        glGetString(GL_SHADING_LANGUAGE_VERSION))));

        // Set the background color to blue
        //glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

        // Set VSYNC
        SDL_GL_SetSwapInterval(0);

        // Enable alpha blend
        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        return 0;
    }

    void Window::SwapBuffer() {
        SDL_GL_SwapWindow(m_sdlWindow);
    }

    void Window::SetWindowSize(int width, int height) {
        m_screenWidth = width;
        m_screenHeight = height;
        SDL_SetWindowSize(m_sdlWindow, m_screenWidth, m_screenHeight);
    }
}  // namespace CrossEngine
