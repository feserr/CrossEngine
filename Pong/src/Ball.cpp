/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "Ball.h"

#include <CrossEngine/ResourceManager.h>
#include <SDL/SDL.h>
#include <random>

void Ball::Init(float radius, float mass, const glm::vec2& pos,
    const glm::vec2& vel) {
    m_radius = radius;
    m_mass = mass;
    m_position = pos;
    m_velocity = vel;
    m_texture.Init(
        CrossEngine::ResourceManager::GetTexture("images/Pong.png"),
        glm::ivec2(8, 1));
    m_color = CrossEngine::ColorRGBA8(255, 255, 255, 255);
}

void Ball::Destroy() {
}

int Ball::Update(float deltaTime, glm::vec2 &windowSize) {
    const float FRICTION = 0.01f;

    glm::vec2 gravity(0.0f);

    m_position += m_velocity * deltaTime;
    // Apply friction
    glm::vec2 momentumVec = m_velocity * m_mass;
    if (momentumVec.x != 0 || momentumVec.y != 0) {
        if (FRICTION < glm::length(momentumVec)) {
            m_velocity -= deltaTime * FRICTION * glm::normalize(momentumVec) /
            m_mass;
        } else {
            m_velocity = glm::vec2(0.0f);
        }
    }

    // Apply gravity
    m_velocity += gravity * deltaTime;

    // Check wall collision
    if (m_position.x < m_radius) {
        m_position.x = m_radius;
        if (m_velocity.x < 0) {
            //m_velocity.x *= -1;
            RestartPosition(windowSize);
            return 1;
        }
    } else if (m_position.x + m_radius >= windowSize.x) {
        m_position.x = windowSize.x - m_radius - 1;
        if (m_velocity.x > 0) {
            //m_velocity.x *= -1;
            RestartPosition(windowSize);
            return 2;
        }
    }

    if (m_position.y < m_radius) {
        m_position.y = m_radius;
        if (m_velocity.y < 0) {
            m_velocity.y *= -1;
        }
    } else if (m_position.y + m_radius >= windowSize.y) {
        m_position.y = windowSize.y - m_radius - 1;
        if (m_velocity.y > 0) {
            m_velocity.y *= -1;
        }
    }

    return 0;
}

void Ball::Draw(CrossEngine::SpriteBatch& spriteBatch) {
    // Get the uv coordinates from the tile index
    glm::vec4 uvRect = m_texture.GetUVs(6);
    const glm::vec4 destRect(m_position.x - m_radius, m_position.y - m_radius,
        m_radius * 2.0f, m_radius * 2.0f);
    spriteBatch.Draw(destRect, uvRect, m_texture.texture.texture, 0.0f,
        m_color);
}

void Ball::RestartPosition(glm::vec2 &windowSize) {
    std::mt19937 randomEngine((unsigned int)time(nullptr));
    std::uniform_real_distribution<float> r1(-1.0f, 1.0f);
    m_position = glm::vec2(windowSize.x / 2, windowSize.y / 2);
    m_velocity = glm::vec2(6 * std::copysign(1.0f, r1(randomEngine)),
        r1(randomEngine));
}
