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

#include "App.h"

#include <CrossEngine/ScreenList.h>
#include <CrossEngine/CppUtils.h>

#if __cplusplus > 199711L
#else
#include <memory>
#endif

App::App() {
}

App::~App() {
}

void App::OnInit() {
    //m_window.SetWindowName("Pong");
    //m_window.SetWindowSize(640, 480);
}

void App::AddScreens() {
    //m_mainMenuScreen = std::make_unique<MainMenuScreen>(&m_window);
#if __cplusplus > 199711L
    m_gameplayScreen = CrossEngine::make_unique<GameplayScreen>(&m_window);
#else
    m_gameplayScreen = std::make_unique<GameplayScreen>(&m_window);
#endif

    //m_screenList->AddScreen(m_mainMenuScreen.get());
    m_screenList->AddScreen(m_gameplayScreen.get());

    m_screenList->SetScreen(m_gameplayScreen->GetScreenIndex());
}

void App::OnExit() {

}