/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "crossengine/particle_engine_2d.h"

#include "crossengine/particle_batch_2d.h"
#include "crossengine/sprite_batch.h"

namespace CrossEngine {
ParticleEngine2D::ParticleEngine2D() {
  // Empty
}

ParticleEngine2D::~ParticleEngine2D() {
  for (auto& b : batches_) {
    delete b;
  }
}

void ParticleEngine2D::AddParticleBatch(ParticleBatch2D* particle_batch) {
  batches_.push_back(particle_batch);
}

void ParticleEngine2D::Update(float delta_time) {
  for (auto& b : batches_) {
    b->Update(delta_time);
  }
}

void ParticleEngine2D::Draw(SpriteBatch* sprite_batch) {
  for (auto& b : batches_) {
    sprite_batch->Begin();
    b->Draw(sprite_batch);
    sprite_batch->End();
    sprite_batch->RenderBatch();
  }
}
}  // namespace CrossEngine
