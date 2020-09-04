/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "crossengine/particle_batch_2d.h"

namespace CrossEngine {
ParticleBatch2D::ParticleBatch2D()
    : decay_rate_(0.1f),
      particles_(nullptr),
      max_particles_(0),
      last_free_particle_(0),
      texture_() {}

ParticleBatch2D::~ParticleBatch2D() { delete[] particles_; }

void ParticleBatch2D::Init(
    int maxParticles, float decay_rate, const CrossTexture& texture,
    std::function<void(Particle2D*, float)> update_func) {
  max_particles_ = maxParticles;
  particles_ = new Particle2D[maxParticles];
  decay_rate_ = decay_rate;
  texture_ = texture;
  update_function_ = update_func;
}

void ParticleBatch2D::Update(float delta_time) {
  for (int i = 0; i < max_particles_; i++) {
    // Check if it is active
    if (particles_[i].life > 0.0f) {
      // Update using function pointer
      update_function_(&particles_[i], delta_time);
      particles_[i].life -= decay_rate_ * delta_time;
    }
  }
}

void ParticleBatch2D::Draw(SpriteBatch* sprite_batch) {
  Rect uv_rect = {0.0f, 0.0f, 1.0f, 1.0f};
  for (int i = 0; i < max_particles_; i++) {
    // Check if it is active
    auto& p = particles_[i];
    if (p.life > 0.0f) {
      Rect dest_rect = {p.position.x, p.position.y, p.width, p.width};
      sprite_batch->Draw(dest_rect, uv_rect, texture_.texture, 0.0f, p.color);
    }
  }
}

void ParticleBatch2D::AddParticle(const bx::Vec3& position,
                                  const bx::Vec3& velocity,
                                  const ColorRGBA8& color, float width) {
  int particleIndex = FindFreeParticle();

  auto& p = particles_[particleIndex];

  p.life = 1.0f;
  p.position = position;
  p.velocity = velocity;
  p.color = color;
  p.width = width;
}

int ParticleBatch2D::FindFreeParticle() {
  for (int i = last_free_particle_; i < max_particles_; i++) {
    if (particles_[i].life <= 0.0f) {
      last_free_particle_ = i;
      return i;
    }
  }

  for (int i = 0; i < last_free_particle_; i++) {
    if (particles_[i].life <= 0.0f) {
      last_free_particle_ = i;
      return i;
    }
  }

  // No particles are free, overwrite first particle
  return 0;
}
}  // namespace CrossEngine
