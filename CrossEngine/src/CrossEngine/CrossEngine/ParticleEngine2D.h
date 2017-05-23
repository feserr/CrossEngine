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

#ifndef _PARTICLEENGINE2D_H_
#define _PARTICLEENGINE2D_H_

#include <vector>

namespace CrossEngine {
class ParticleBatch2D;
class SpriteBatch;

class ParticleEngine2D {
 public:
    ParticleEngine2D();
    ~ParticleEngine2D();

    // After adding a particle batch, the ParticleEngine2D becomes
    // responsible for deallocation.
    void AddParticleBatch(ParticleBatch2D* particleBatch);

    void Update(float deltaTime);

    void Draw(SpriteBatch* spriteBatch);

 private:
    std::vector<ParticleBatch2D*> m_batches;
};
}  // namespace CrossEngine

#endif  // _PARTICLEENGINE2D_H_
