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

#include "CrossEngine/ScreenList.h"
#include "CrossEngine/IGameScreen.h"

#include <cstdio>

namespace CrossEngine {
    ScreenList::ScreenList(IMainGame* game) :
        m_game(game) {
        // Empty
    }

    ScreenList::~ScreenList() {
        Destroy();
    }

    IGameScreen* CrossEngine::ScreenList::MoveNext() {
        IGameScreen* currentScreen = GetCurrent();
        if (currentScreen->GetNextScreenIndex() != SCREEN_INDEX_NO_SCREEN) {
            m_currentScreenIndex = currentScreen->GetNextScreenIndex();
        }
        return GetCurrent();
    }

    IGameScreen* CrossEngine::ScreenList::MovePrevious() {
        IGameScreen* currentScreen = GetCurrent();
        if (currentScreen->GetPreviousScreenIndex() != SCREEN_INDEX_NO_SCREEN) {
            m_currentScreenIndex = currentScreen->GetPreviousScreenIndex();
        }
        return GetCurrent();
    }

    void CrossEngine::ScreenList::SetScreen(int nextScreen) {
        m_currentScreenIndex = nextScreen;
    }

    void CrossEngine::ScreenList::AddScreen(IGameScreen* newScreen) {
        newScreen->m_screenIndex = static_cast<int>(m_screens.size());
        m_screens.push_back(newScreen);
        newScreen->Build();
        newScreen->SetParentGame(m_game);
    }

    void CrossEngine::ScreenList::Destroy() {
        for (size_t i = 0; i < m_screens.size(); i++) {
            m_screens[i]->Destroy();
        }
        m_screens.resize(0);
        m_currentScreenIndex = SCREEN_INDEX_NO_SCREEN;
    }

    IGameScreen* ScreenList::GetCurrent() {
        if (m_currentScreenIndex == SCREEN_INDEX_NO_SCREEN) return nullptr;
        return m_screens[m_currentScreenIndex];
    }
}  // namespace CrossEngine
