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

#include "Player.h"

#include <CrossEngine/ResourceManager.h>
#include <SDL/SDL.h>
#include <iostream>

const float MAX_VELOCITY = 5.0f;

void Player::Init(const glm::vec2& position, const glm::vec2& drawDims,
    glm::vec2& collisionDims, CrossEngine::ColorRGBA8 color,
    PlayerType playerType) {
    CrossEngine::GLTexture texture =
        CrossEngine::ResourceManager::GetTexture(
        "Assets/Pong/Sprites/Pong.png");
    m_color = color;
    m_drawDims = drawDims;
    m_collisionDims = collisionDims;
    m_position = position;
    m_velocity = glm::vec2(0.0f);
    m_texture.Init(texture, glm::ivec2(8, 1));
    m_playerType = playerType;
}

void Player::Destroy() {
}

void Player::Draw(CrossEngine::SpriteBatch& spriteBatch) {
    glm::vec4 destRect;
    destRect.x = m_position.x - m_drawDims.x / 2.0f;
    destRect.y = m_position.y - m_drawDims.y / 2.0f;
    destRect.z = m_drawDims.x;
    destRect.w = m_drawDims.y;

    int tileIndex;
    int numTiles;

    glm::vec2 velocity;
    velocity.x = m_velocity.x;
    velocity.y = m_velocity.y;

    if (std::abs(velocity.y) > 1.0f) {
        // Moving
        numTiles = 1;
        tileIndex = 0;
        m_moveState = PlayerMoveState::MOVING;
    } else {
        // Standing still
        numTiles = 1;
        tileIndex = 0;
        m_moveState = PlayerMoveState::STANDING;
    }

    // Get the uv coordinates from the tile index
    glm::vec4 uvRect = m_texture.GetUVs(tileIndex);
    glm::vec4 uvRectBottom = m_texture.GetUVs(tileIndex+1);
    glm::vec4 uvRectTop = m_texture.GetUVs(tileIndex+2);

    // Draw the sprite
    spriteBatch.Draw(destRect, uvRect, m_texture.texture.id, 0.0f, m_color);
    destRect.y = m_position.y + m_drawDims.y / 2;
    spriteBatch.Draw(destRect, uvRectBottom, m_texture.texture.id, 0.0f, 
        m_color);
    destRect.y = m_position.y - m_drawDims.y * 1.5;
    spriteBatch.Draw(destRect, uvRectTop, m_texture.texture.id, 0.0f, m_color);
}

void Player::DrawDebug(CrossEngine::DebugRenderer& debugRenderer) {
    CrossEngine::ColorRGBA8 color(255, 255, 0, 255);
    // Draw box
    glm::vec4 destRect;
    destRect.x = m_position.x - m_drawDims.x / 2.0f;
    destRect.y = m_position.y - m_drawDims.y / 2.0f;
    destRect.z = m_drawDims.x;
    destRect.w = m_drawDims.y;
    debugRenderer.DrawBox(destRect, color, 0.0f);
}

void Player::Update(float deltaTime, CrossEngine::InputManager& inputManager,
    const glm::vec2 &windowSize) {
    // Check inputs and update the player stats
    if (inputManager.IsKeyDown(SDLK_w) &&
        m_playerType == PlayerType::PLAYERONE) {
        m_velocity.y = MAX_VELOCITY;
    } else if (inputManager.IsKeyDown(SDLK_s) &&
        m_playerType == PlayerType::PLAYERONE) {
        m_velocity.y = -MAX_VELOCITY;
    } else if (inputManager.IsKeyDown(SDLK_UP) &&
        m_playerType == PlayerType::PLAYERTWO) {
        m_velocity.y = MAX_VELOCITY;
    } else if (inputManager.IsKeyDown(SDLK_DOWN) &&
        m_playerType == PlayerType::PLAYERTWO) {
        m_velocity.y = -MAX_VELOCITY;
    }

    // Check if the player goes out of the window
    if (m_velocity.y < 0 && m_position.y -  m_drawDims.y <= 0) {
        m_velocity.y = 0;
    } else if (m_velocity.y > 0 &&
        m_position.y +  m_drawDims.y >= windowSize.y) {
        m_velocity.y = 0;
    }

    // Set position
    m_position += m_velocity * deltaTime;

    // Handle the velocity
    if (std::abs(m_velocity.y) > 0.01f) {
        m_velocity.y = (std::abs(m_velocity.y) - MAX_VELOCITY / 2) *
            (m_velocity.y > 0 ? 1 : -1);
    } else {
        m_velocity.y = 0.0f;
    }
}
