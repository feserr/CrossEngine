/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
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
