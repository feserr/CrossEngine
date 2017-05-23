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

#include "CrossEngine/ParticleBatch2D.h"

namespace CrossEngine {
    ParticleBatch2D::ParticleBatch2D() {
        // Empty
    }


    ParticleBatch2D::~ParticleBatch2D() {
        delete[] m_particles;
    }

    void ParticleBatch2D::Init(int maxParticles, float decayRate,
        CrossTexture texture, std::function<void(Particle2D*, float)> updateFunc) {
        m_maxParticles = maxParticles;
        m_particles = new Particle2D[maxParticles];
        m_decayRate = decayRate;
        m_texture = texture;
        m_updateFunc = updateFunc;
    }

    void ParticleBatch2D::Update(float deltaTime) {
        for (int i = 0; i < m_maxParticles; i++) {
            // Check if it is active
            if (m_particles[i].life > 0.0f) {
                // Update using function pointer
                m_updateFunc(&m_particles[i], deltaTime);
                m_particles[i].life -= m_decayRate * deltaTime;
            }
        }
    }

    void ParticleBatch2D::Draw(SpriteBatch* spriteBatch) {
        glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
        for (int i = 0; i < m_maxParticles; i++) {
            // Check if it is active
            auto& p = m_particles[i];
            if (p.life > 0.0f) {
                glm::vec4 destRect(p.position.x, p.position.y, p.width,
                    p.width);
                spriteBatch->Draw(destRect, uvRect, m_texture.texture, 0.0f,
                    p.color);
            }
        }
    }

    void ParticleBatch2D::AddParticle(const glm::vec2& position,
        const glm::vec2& velocity, const ColorRGBA8& color, float width) {
        int particleIndex = FindFreeParticle();

        auto& p = m_particles[particleIndex];

        p.life = 1.0f;
        p.position = position;
        p.velocity = velocity;
        p.color = color;
        p.width = width;
    }

    int ParticleBatch2D::FindFreeParticle() {
        for (int i = m_lastFreeParticle; i < m_maxParticles; i++) {
            if (m_particles[i].life <= 0.0f) {
                m_lastFreeParticle = i;
                return i;
            }
        }

        for (int i = 0; i < m_lastFreeParticle; i++) {
            if (m_particles[i].life <= 0.0f) {
                m_lastFreeParticle = i;
                return i;
            }
        }

        // No particles are free, overwrite first particle
        return 0;
    }
}  // namespace CrossEngine
