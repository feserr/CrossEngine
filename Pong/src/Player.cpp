/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "Player.h"

#include <CrossEngine/ResourceManager.h>
#include <SDL/SDL.h>
#include <iostream>

#include <common/common.h>
#include <common/bgfx_utils.h>
#include <common/entry/entry.h>
#include <common/entry/input.h>

const float MAX_VELOCITY = 5.0f;

void Player::Init(const glm::vec2& position, const glm::vec2& drawDims,
    glm::vec2& collisionDims, CrossEngine::ColorRGBA8 color,
    PlayerType playerType) {
    m_color = color;
    m_drawDims = drawDims;
    m_collisionDims = collisionDims;
    m_position = position;
    m_velocity = glm::vec2(0.0f);
    m_texture.Init(CrossEngine::ResourceManager::GetTexture("images/Pong.png"),
        glm::ivec2(8, 1));
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
    //m_sprite.Draw(&m_texture);
    // Draw the sprite
    spriteBatch.Draw(destRect, uvRect, m_texture.texture.texture, 0.0f,
        m_color);
    destRect.y = m_position.y + m_drawDims.y / 2;
    spriteBatch.Draw(destRect, uvRectTop, m_texture.texture.texture, 0.0f,
        m_color);
    destRect.y = m_position.y - m_drawDims.y * 1.5;
    spriteBatch.Draw(destRect, uvRectBottom, m_texture.texture.texture, 0.0f,
        m_color);
}

void Player::Update(float deltaTime, CrossEngine::InputManager& inputManager,
    const glm::vec2 &windowSize, Ball &ball) {
    // Check inputs and update the player stats
    if (inputManager.IsKeyDown(entry::Key::KeyW) &&
        m_playerType == PlayerType::PLAYERONE) {
        m_velocity.y = -MAX_VELOCITY;
    } else if (inputManager.IsKeyDown(entry::Key::KeyS) &&
        m_playerType == PlayerType::PLAYERONE) {
        m_velocity.y = MAX_VELOCITY;
    } else if (inputManager.IsKeyDown(entry::Key::Up) &&
        m_playerType == PlayerType::PLAYERTWO) {
        m_velocity.y = -MAX_VELOCITY;
    } else if (inputManager.IsKeyDown(entry::Key::Down) &&
        m_playerType == PlayerType::PLAYERTWO) {
        m_velocity.y = MAX_VELOCITY;
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

    // Ball collision
    glm::vec2 ballPosition = ball.GetPosition();
    glm::vec2 newVelocity;
    // Check if they are at the same y position
    if(m_position.y - m_collisionDims.y / 2 <= ballPosition.y + ball.GetRadius() &&
       m_position.y + m_collisionDims.y / 2 >= ballPosition.y - ball.GetRadius())
    {
        float yCollision = (ballPosition.y - m_position.y) / 4;
        if (m_playerType == PlayerType::PLAYERONE &&
            m_position.x + m_collisionDims.x >= ballPosition.x + ball.GetRadius()) {
            newVelocity = glm::vec2(6.0f, yCollision);
            ball.SetVelocity(newVelocity);
        } else if (m_playerType == PlayerType::PLAYERTWO &&
                   m_position.x - m_collisionDims.x <= ballPosition.x - ball.GetRadius()) {
            newVelocity = glm::vec2(-6.0f, yCollision);
            ball.SetVelocity(newVelocity);
        }
    }
}
