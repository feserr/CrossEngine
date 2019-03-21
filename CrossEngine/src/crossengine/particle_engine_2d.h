/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_PARTICLEENGINE2D_H_
#define CROSSENGINE_PARTICLEENGINE2D_H_

#include <vector>

namespace CrossEngine {
class ParticleBatch2D;
class SpriteBatch;

/**
 * @brief Class to manage ParticleBatch2D.
 */
class ParticleEngine2D {
 public:
  /**
   * @brief Construct a new ParticleEngine2D object.
   */
  ParticleEngine2D();

  /**
   * @brief Destroy the ParticleEngine2D object.
   */
  ~ParticleEngine2D();

  /**
   * @brief Adds a ParticleBatch2D to the engine.
   * After adding a particle batch, the ParticleEngine2D becomes responsible
   * for deallocation.
   *
   * @param[in] particle_batch The ParticleBatch2D.
   */
  void AddParticleBatch(ParticleBatch2D* particle_batch);

  /**
   * @brief Updates the particle engine.
   *
   * @param[in] deltaTime The delta time.
   */
  void Update(float deltaTime);

  /**
   * @brief Renders the ParticlesBatch2D of the engine.
   *
   * @param[in] sprite_batch The SpriteBatch containing the sprites to render.
   */
  void Draw(SpriteBatch* sprite_batch);

 private:
  std::vector<ParticleBatch2D*> batches_;
};
}  // namespace CrossEngine

#endif  // CROSSENGINE_PARTICLEENGINE2D_H_
