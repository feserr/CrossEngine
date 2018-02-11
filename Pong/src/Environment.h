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

#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include <CrossEngine/InputManager.h>
#include <CrossEngine/SpriteBatch.h>
#include <CrossEngine/TileSheet.h>

class Environment {
  public:
    void Init(const glm::vec2& position, const glm::vec2& dimension,
        CrossEngine::ColorRGBA8 color);

    void Destroy();

    void Draw(CrossEngine::SpriteBatch& spriteBatch);

  private:
    glm::vec2 m_position;
    glm::vec2 m_dimension;
    CrossEngine::ColorRGBA8 m_color;
    CrossEngine::TileSheet m_texture;
};

#endif  // _ENVIRONMENT_H_
