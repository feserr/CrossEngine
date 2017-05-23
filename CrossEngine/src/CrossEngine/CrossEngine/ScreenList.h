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

#ifndef _SCREENLIST_H_
#define _SCREENLIST_H_

#include <vector>

namespace CrossEngine {
class IMainGame;
class IGameScreen;

class ScreenList {
 public:
    explicit ScreenList(IMainGame* game);
    ~ScreenList();

    IGameScreen* MoveNext();
    IGameScreen* MovePrevious();

    void SetScreen(int nextScreen);
    void AddScreen(IGameScreen* newScreen);

    void Destroy();

    IGameScreen* GetCurrent();

 protected:
    IMainGame* m_game = nullptr;
    std::vector<IGameScreen*> m_screens;
    int m_currentScreenIndex = -1;
};
}  // namespace CrossEngine

#endif  // _SCREENLIST_H_
