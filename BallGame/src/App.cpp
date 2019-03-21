/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
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
    m_window.SetWindowName("BallGame");
    m_window.SetWindowSize(1280, 720);
}

void App::AddScreens() {
    //m_mainMenuScreen = std::make_unique<MainMenuScreen>(&m_window);
#if __cplusplus > 199711L
    m_gameplayScreen = CrossEngine::make_unique<MainGame>(&m_window);
#else
    m_gameplayScreen = std::make_unique<GameplayScreen>(&m_window);
#endif

    //m_screenList->AddScreen(m_mainMenuScreen.get());
    m_screenList->AddScreen(m_gameplayScreen.get());

    m_screenList->SetScreen(m_gameplayScreen->GetScreenIndex());
}

void App::OnExit() {

}
