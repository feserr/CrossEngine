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

#include "CrossEngine/ParticleEngine2D.h"
#include "CrossEngine/ParticleBatch2D.h"
#include "CrossEngine/SpriteBatch.h"

namespace CrossEngine {
    ParticleEngine2D::ParticleEngine2D() {
        // Empty
    }

    ParticleEngine2D::~ParticleEngine2D() {
        for (auto& b : m_batches) {
            delete b;
        }
    }

    void ParticleEngine2D::AddParticleBatch(ParticleBatch2D* particleBatch) {
        m_batches.push_back(particleBatch);
    }

    void ParticleEngine2D::Update(float deltaTime) {
        for (auto& b : m_batches) {
            b->Update(deltaTime);
        }
    }

    void ParticleEngine2D::Draw(SpriteBatch* spriteBatch) {
        for (auto& b : m_batches) {
            spriteBatch->Begin();
            b->Draw(spriteBatch);
            spriteBatch->End();
            spriteBatch->RenderBatch();
        }
    }
}  // namespace CrossEngine
