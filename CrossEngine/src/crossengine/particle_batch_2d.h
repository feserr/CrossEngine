/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_PARTICLEBATCH2D_H_
#define CROSSENGINE_PARTICLEBATCH2D_H_

#include <bx/math.h>

#include <functional>

#include "cross_texture.h"
#include "sprite_batch.h"
#include "vertex.h"

namespace CrossEngine {
/**
 * @brief Particle 2D class.
 */
class Particle2D {
 public:
  bx::Vec3 position;
  bx::Vec3 velocity;
  ColorRGBA8 color;
  float life;
  float width;
};

/**
 * @brief Default function pointer.
 *
 * @param[in] particle The particle.
 * @param[in] delta_time The delta time.
 */
inline void DefaultParticleUpdate(Particle2D* particle, float delta_time) {
  particle->position =
      bx::add(particle->position, bx::mul(particle->velocity, delta_time));
}

/**
 * @brief A class to render the Particle2D.
 */
class ParticleBatch2D {
 public:
  /**
   * @brief Construct a new ParticleBatch2D object.
   */
  ParticleBatch2D();

  /**
   * @brief Destroy the ParticleBatch2D object.
   */
  ~ParticleBatch2D();

  /**
   * @brief Initialize the object.
   *
   * @param[in] max_particles The maximun number of particles.
   * @param[in] decay_rate The decay rate.
   * @param[in] texture The CrossEngine texture.
   * @param[in] update_function The update function.
   */
  void Init(int max_particles, float decay_rate, const CrossTexture& texture,
            std::function<void(Particle2D*, float)> update_function =
                DefaultParticleUpdate);

  /**
   * @brief Update the object.
   *
   * @param[in] delta_time The delta time.
   */
  void Update(float delta_time);

  /**
   * @brief Render the object.
   *
   * @param[in] sprite_batch The SpriteBatch.
   */
  void Draw(SpriteBatch* sprite_batch);

  /**
   * @brief Adds a particle.
   *
   * @param[in] position The position.
   * @param[in] velocity The velocity.
   * @param[in] color The color.
   * @param[in] width The width.
   */
  void AddParticle(const bx::Vec3& position, const bx::Vec3& velocity,
                   const ColorRGBA8& color, float width);

 private:
  int FindFreeParticle();

  std::function<void(Particle2D*, float)> update_function_;

  float decay_rate_;
  Particle2D* particles_;
  int max_particles_;
  int last_free_particle_;
  CrossTexture texture_;
};
}  // namespace CrossEngine

#endif  // _PARTICLEBATCH2CROSSENGINE_PARTICLEBATCH2D_H_D_H_
