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

#ifndef _PARTICLEBATCH2D_H_
#define _PARTICLEBATCH2D_H_

#include "Vertex.h"
#include "SpriteBatch.h"
#include "CrossTexture.h"

#include <glm/glm.hpp>
#include <functional>

namespace CrossEngine {
class Particle2D {
 public:
    glm::vec2 position = glm::vec2(0.0f);
    glm::vec2 velocity = glm::vec2(0.0f);
    ColorRGBA8 color;
    float life = 0.0f;
    float width = 0.0f;
};

// Default function pointer
inline void defaultParticleUpdate(Particle2D* particle, float deltaTime) {
    particle->position += particle->velocity * deltaTime;
}

class ParticleBatch2D {
 public:
    ParticleBatch2D();
    ~ParticleBatch2D();

    void Init(int maxParticles, float decayRate, CrossTexture texture,
        std::function<void(Particle2D*, float)> updateFunc =
        defaultParticleUpdate);

    void Update(float deltaTime);

    void Draw(SpriteBatch* spriteBatch);

    void AddParticle(const glm::vec2& position, const glm::vec2& velocity,
        const ColorRGBA8& color, float width);

 private:
    int FindFreeParticle();

    /// Function pointer for custom updates
    std::function<void(Particle2D*, float)> m_updateFunc;

    float m_decayRate = 0.1f;
    Particle2D* m_particles = nullptr;
    int m_maxParticles = 0;
    int m_lastFreeParticle = 0;
    CrossTexture m_texture;
};
}  // namespace CrossEngine

#endif  // _PARTICLEBATCH2D_H_
