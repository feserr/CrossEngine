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

#include "Environment.h"

#include <CrossEngine/ResourceManager.h>

void Environment::Init(const glm::vec2& position,
    const glm::vec2& dimension, CrossEngine::ColorRGBA8 color) {
    CrossEngine::CrossTexture texture =
        CrossEngine::ResourceManager::GetTexture("images/Pong.png");
    m_color = color;
    m_dimension = dimension;
    m_position = position;
    m_texture.Init(texture, glm::ivec2(8, 1));
}

void Environment::Destroy() {
}

void Environment::Draw(CrossEngine::SpriteBatch& spriteBatch) {
    glm::vec4 destRect;
    destRect.x = m_position.x - m_dimension.x / 2.0f;
    destRect.y = m_position.y - m_dimension.y / 2.0f;
    destRect.z = m_dimension.x;
    destRect.w = m_dimension.y;

    glm::vec4 uvRect = m_texture.GetUVs(7);

    spriteBatch.Draw(destRect, uvRect, m_texture.texture.texture, 0.0f,
        m_color);
}
