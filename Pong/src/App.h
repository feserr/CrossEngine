/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef App_h
#define App_h

#include "GameplayScreen.h"
//#include "MainMenuScreen.h"

#include <CrossEngine/IMainGame.h>

// Our custom app that inherits from IMainGame
class App : public CrossEngine::IMainGame{
 public:
    App();
    ~App();

    // Called on initialization
    virtual void OnInit() override;
    // For adding all screens
    virtual void AddScreens() override;
    // Called when exiting
    virtual void OnExit() override;
 private:
    std::unique_ptr<GameplayScreen> m_gameplayScreen = nullptr;

    CrossEngine::Window m_window;
};

#endif /* App_h */
