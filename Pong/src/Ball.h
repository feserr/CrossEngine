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
