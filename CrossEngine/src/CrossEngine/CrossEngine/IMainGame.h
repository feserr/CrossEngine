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

#ifndef _IMAINGAME_H_
#define _IMAINGAME_H_

#include "CrossEngine.h"
#include "Window.h"
#include "InputManager.h"
#include "Timing.h"

#include "../../common.h"

#include <memory>

namespace CrossEngine {
class ScreenList;
class IGameScreen;

/// Main game interface.
class IMainGame : public entry::AppI {
 public:
    /// Default constructor.
    IMainGame();

    /// Default destructor.
    virtual ~IMainGame();

    /// Runs and initializes the game.
    bool update();
    /// Exits the game.
    virtual int shutdown();

    /// Called on initialization.
    virtual void OnInit() = 0;
    /// For adding all screens.
    virtual void AddScreens() = 0;
    /// Called when exiting.
    virtual void OnExit() = 0;

    /**
     * \brief      Handle SDL events.
     *
     * \param[in]  evnt  The event.
     */
    void OnSDLEvent(const SDL_Event& evnt);

    /**
     * \brief      Gets the FPS.
     *
     * \return     The FPS.
     */
    const float GetFps() const { return m_fps; }

    /// The input manager.
    InputManager inputManager;

 protected:
    /// Custom update function
    virtual void Update();
    /// Custom render function
    virtual void Draw();

    /**
     * \brief      Initialize the main game.
     *
     * \return     
     */
    void init(int _argc, char** _argv);
    bool InitSystems(int _argc, char** _argv);

    std::unique_ptr<ScreenList> m_screenList;
    IGameScreen* m_currentScreen = nullptr;
    bool m_isRunning = false;
    float m_fps = 0.0f;

 private:
    FpsLimiter m_limiter;

    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_debug;
    uint32_t m_reset;
};
}  // namespace CrossEngine

#endif  // _IMAINGAME_H_
