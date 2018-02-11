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

#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#include "../../common/common.h"

#include <glm/glm.hpp>
#include <unordered_map>

namespace CrossEngine {
// Input manager stores a key map that maps SDL_Keys to booleans.
// If the value in the key map is true, then the key is pressed.
// Otherwise, it is released.
class InputManager {
 public:
    InputManager();
    ~InputManager();

    void Update();

    void PressKey(unsigned int keyID);
    void ReleaseKey(unsigned int keyID);

    void SetMouseCoords(float x, float y);

    /// Returns true if the key is held down
    bool IsKeyDown(unsigned int keyID);
    bool IsKeyDown(entry::Key::Enum keyID);

    /// Returns true if the key was just pressed
    bool IsKeyPressed(unsigned int keyID);

    // Getters
    glm::vec2 GetMouseCoords() const { return m_mouseCoords; }

 private:
    /// Returns true if the key is held down
    bool WasKeyDown(unsigned int keyID);

    std::unordered_map<unsigned int, bool> m_keyMap;
    std::unordered_map<unsigned int, bool> m_previousKeyMap;
    glm::vec2 m_mouseCoords;
};
}  // namespace CrossEngine

#endif  // _INPUTMANAGER_H_
