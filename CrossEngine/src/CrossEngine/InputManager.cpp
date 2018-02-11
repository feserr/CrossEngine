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

#include "CrossEngine/InputManager.h"

#include "../common/entry/input.h"

namespace CrossEngine {
    InputManager::InputManager() : m_mouseCoords(0.0f) {
    }


    InputManager::~InputManager() {
    }

    void InputManager::Update() {
        // Loop through m_keyMap using a for each loop, and copy it over to
        // m_previousKeyMap
        for (auto& it : m_keyMap) {
            m_previousKeyMap[it.first] = it.second;
        }
    }

    void InputManager::PressKey(unsigned int keyID) {
        // Here we are treating m_keyMap as an associative array.
        // if keyID doesn't already exist in m_keyMap, it will get added
        m_keyMap[keyID] = true;
    }

    void InputManager::ReleaseKey(unsigned int keyID) {
        m_keyMap[keyID] = false;
    }

    void InputManager::SetMouseCoords(float x, float y) {
        m_mouseCoords.x = x;
        m_mouseCoords.y = y;
    }

    bool InputManager::IsKeyDown(unsigned int keyID) {
        // We dont want to use the associative array approach here
        // because we don't want to create a key if it doesnt exist.
        // So we do it manually
        auto it = m_keyMap.find(keyID);
        if (it != m_keyMap.end()) {
            // Found the key
            return it->second;
        } else {
            // Didn't find the key
            return false;
        }
    }

    bool InputManager::IsKeyDown(entry::Key::Enum keyID) {
        return inputGetKeyState(keyID);
    }

    bool InputManager::IsKeyPressed(unsigned int keyID) {
        // Check if it is pressed this frame, and wasn't pressed last frame
        if (IsKeyDown(keyID) == true && WasKeyDown(keyID) == false) {
            return true;
        }
        return false;
    }

    bool InputManager::WasKeyDown(unsigned int keyID) {
        // We dont want to use the associative array approach here
        // because we don't want to create a key if it doesnt exist.
        // So we do it manually
        auto it = m_previousKeyMap.find(keyID);
        if (it != m_previousKeyMap.end()) {
            // Found the key
            return it->second;
        } else {
            // Didn't find the key
            return false;
        }
    }
}  // namespace CrossEngine
