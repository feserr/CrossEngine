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

#include "CrossEngine/IMainGame.h"
#include "CrossEngine/ScreenList.h"
#include "CrossEngine/IGameScreen.h"
#include "CrossEngine/CppUtils.h"

#include "../common.h"
#include "../bgfx_utils.h"
#include "../entry/entry.h"
#include "../entry/input.h"

#include <memory>

namespace CrossEngine {
IMainGame::IMainGame() {
#if __cplusplus > 199711L
    m_screenList = CrossEngine::make_unique<ScreenList>(this);
#else
    m_screenList = std::make_unique<ScreenList>(this);
#endif
}

IMainGame::~IMainGame() {
    // Empty
}

void IMainGame::Run(int _argc, char** _argv) {
    if (!Init(_argc, _argv)) return;

    FpsLimiter limiter;
    limiter.SetMaxFPS(60.0f);

    // Game loop
    m_isRunning = true;
    while (m_isRunning) {
        if (!entry::processEvents(m_width, m_height, m_debug, m_reset) ) {
            limiter.Begin();

            bgfx::touch(0);

            inputManager.Update();
            // Call the custom update and draw method
            Update();
            if (m_isRunning) {
                Draw();

                m_fps = limiter.End();
                // Advance to next frame. Rendering thread will be kicked to
                // process submitted rendering primitives.
                bgfx::frame();
            }
        }
    }
}

int IMainGame::ExitGame() {
    if (m_currentScreen) {
        m_currentScreen->OnExit();
    }

    if (m_screenList) {
        m_screenList->Destroy();
        m_screenList.reset();
    }
    m_isRunning = false;

    // Shutdown bgfx.
    bgfx::shutdown();

    return 0;
}

void IMainGame::OnSDLEvent(const SDL_Event& evnt) {
    switch (evnt.type) {
        case SDL_QUIT:
            ExitGame();
            break;
        case SDL_MOUSEMOTION:
            inputManager.SetMouseCoords(
                static_cast<float>(evnt.motion.x),
                static_cast<float>(evnt.motion.y));
            break;
        case SDL_KEYDOWN:
            inputManager.PressKey(evnt.key.keysym.sym);
            break;
        case SDL_KEYUP:
            inputManager.ReleaseKey(evnt.key.keysym.sym);
            break;
        case SDL_MOUSEBUTTONDOWN:
            inputManager.PressKey(evnt.button.button);
            break;
        case SDL_MOUSEBUTTONUP:
            inputManager.ReleaseKey(evnt.button.button);
            break;
    }
}

bool IMainGame::Init(int _argc, char** _argv) {
    CrossEngine::Init();

    if (!InitSystems(_argc, _argv)) return false;

    OnInit();
    AddScreens();

    m_currentScreen = m_screenList->GetCurrent();
    if (m_currentScreen) {
        m_currentScreen->OnEntry();
        m_currentScreen->SetRunning();
    }

    // Game loop
    m_isRunning = true;

    return true;
}

bool IMainGame::InitSystems(int _argc, char** _argv) {
    Args args(_argc, _argv);

    m_width  = 640;
    m_height = 480;
    m_debug  = BGFX_DEBUG_TEXT;
    m_reset  = BGFX_RESET_VSYNC;

    bgfx::init(args.m_type, args.m_pciId);
    bgfx::reset(m_width, m_height, m_reset);

    // Enable debug text.
    bgfx::setDebug(m_debug);

    // Set view 0 clear state.
    bgfx::setViewClear(0,
        BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH,
        0x303030ff,
        1.0f,
        0);

    return true;
}


void IMainGame::Update() {
    if (m_currentScreen) {
        switch (m_currentScreen->GetState()) {
            case ScreenState::RUNNING:
                m_currentScreen->Update();
                break;
            case ScreenState::CHANGE_NEXT:
                m_currentScreen->OnExit();
                m_currentScreen = m_screenList->MoveNext();
                if (m_currentScreen) {
                    m_currentScreen->SetRunning();
                    m_currentScreen->OnEntry();
                }
                break;
            case ScreenState::CHANGE_PREVIOUS:
                m_currentScreen->OnExit();
                m_currentScreen = m_screenList->MovePrevious();
                if (m_currentScreen) {
                    m_currentScreen->SetRunning();
                    m_currentScreen->OnEntry();
                }
                break;
            case ScreenState::EXIT_APPLICATION:
                ExitGame();
                break;
            default:
                break;
        }
    } else {
        ExitGame();
    }
}

void IMainGame::Draw() {
    bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));

    // This dummy draw call is here to make sure that view 0 is cleared
    // if no other draw calls are submitted to view 0.
    bgfx::touch(0);

    if (m_currentScreen && m_currentScreen->GetState() ==
        ScreenState::RUNNING) {
        m_currentScreen->Draw();
    }
}
}  // namespace CrossEngine
