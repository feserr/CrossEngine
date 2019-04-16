/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "crossengine/sprite.h"

#include <cstddef>
#include <string>
#include "crossengine/bgfx_utils.h"
#include "crossengine/resource_manager.h"
#include "crossengine/vertex.h"

namespace CrossEngine {

static PosTexcoordVertex m_cubeVertices[4] = {
    {-1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f},
    {1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f},
    {-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 0.0f},
    {1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 0.0f},
};

static const uint16_t m_cubeIndices[6] = {
    0, 1, 2,  // 0
    1, 3, 2,
};

Sprite::Sprite()
    : x_(0.0f),
      y_(0.0f),
      width_(0.0f),
      height_(0.0f),
      texture_(CrossTexture()) {}

Sprite::~Sprite() {
  if (bgfx::isValid(texture_.texture)) {
    bgfx::destroy(texture_.texture);
  }
  bgfx::destroy(ibh_);
  bgfx::destroy(vbh_);
  if (bgfx::isValid(program_)) {
    bgfx::destroy(program_);
  }
  bgfx::destroy(texture_color_);
}

void Sprite::SetPosition(float x, float y) {
  x_ = x;
  y_ = y;
}

void Sprite::SetDimensions(float width, float height) {
  width_ = width;
  height_ = height;
}

void Sprite::Init(float x, float y, float width, float height,
                  CrossEngine::CrossTexture* texture) {
  // Set up our private vars
  x_ = x;
  y_ = y;
  width_ = width;
  height_ = height;

  texture_ = *texture;

  // Create vertex stream declaration.
  PosTexcoordVertex::Init();

  // Create static vertex buffer.
  vbh_ = bgfx::createVertexBuffer(
      bgfx::makeRef(m_cubeVertices, sizeof(m_cubeVertices)),
      PosTexcoordVertex::ms_decl);

  // Create static index buffer.
  ibh_ = bgfx::createIndexBuffer(
      bgfx::makeRef(m_cubeIndices, sizeof(m_cubeIndices)));

  // Create program from shaders.
  program_ = loadProgram("vs_update", "fs_update_cmp");

  texture_color_ =
      bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
}

// Draws the sprite to the screen
void Sprite::Draw() {
  float mtx[16];
  bx::mtxTranslate(mtx, x_, y_, 0.0f);

  // Set model matrix for rendering.
  bgfx::setTransform(mtx);

  // Set vertex and index buffer.
  bgfx::setVertexBuffer(0, vbh_);
  bgfx::setIndexBuffer(ibh_);

  // Bind texture.
  bgfx::setTexture(0, texture_color_, texture_.texture);

  // Set render states.
  bgfx::setState(BGFX_STATE_DEFAULT);

  // Submit primitive for rendering to view 1.
  bgfx::submit(0, program_);
}
}  // namespace CrossEngine
