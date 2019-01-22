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
