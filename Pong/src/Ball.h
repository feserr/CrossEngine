/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef _BALL_H
#define _BALL_H

#include <CrossEngine/Vertex.h>
#include <CrossEngine/InputManager.h>
#include <CrossEngine/SpriteBatch.h>
#include <CrossEngine/TileSheet.h>

class Ball {
  public:
    void Init(float radius, float mass, const glm::vec2& pos,
         const glm::vec2& vel);

    void Destroy();

    /// Update the ball
    int Update(float deltaTime, glm::vec2 &windowSize);

    void Draw(CrossEngine::SpriteBatch& spriteBatch);

    void RestartPosition(glm::vec2 &windowSize);

    const glm::vec2& GetPosition() { return m_position; }
    const float GetRadius() {return m_radius; }

    void SetVelocity(glm::vec2 &vel) { m_velocity = vel; }

  private:
    glm::vec2 m_position;
    glm::vec2 m_velocity;
    CrossEngine::ColorRGBA8 m_color;
    CrossEngine::TileSheet m_texture;
    float m_radius;
    float m_mass;
};

#endif  // _BALL_H
