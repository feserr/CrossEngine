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

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <SDL/SDL.h>
#include <string>

namespace CrossEngine {
enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

class Window {
 public:
    Window();
    ~Window();

    int Create(std::string windowName, int screenWidth, int screenHeight,
        unsigned int currentFlags);

    void SwapBuffer();

    int GetScreenWidth() { return m_screenWidth; }
    int GetScreenHeight() { return m_screenHeight; }

    void SetWindowName(const char *name) { SDL_SetWindowTitle(m_sdlWindow,
        name); }
    void SetWindowSize(int width, int height);

 private:
    SDL_Window* m_sdlWindow;
    int m_screenWidth, m_screenHeight;
};
}  // namespace CrossEngine

#endif  // _WINDOW_H_
