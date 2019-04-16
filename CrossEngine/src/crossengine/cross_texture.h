/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_TEXTURE_H_
#define CROSSENGINE_TEXTURE_H_

#include <bgfx/bgfx.h>
#include <string>
#include "vertex.h"

namespace CrossEngine {
/**
 * @brief A Cross Engine texture info.
 */
struct CrossTexture {
  std::string file_path = "";   ///< The filepath to the texture
  bgfx::TextureHandle texture;  ///< The texture
  int width;                    ///< The width
  int height;                   ///< The height
};

/**
 * @brief A struct contaning position, texture coordinates and vertex. Useful
 * for shaders.
 */
struct PosTexcoordVertex {
  float x_;
  float y_;
  float z_;
  float u_;
  float v_;
  float w_;
  uint32_t abgr_;

  /**
   * @brief Initialize the struct with default values.
   */
  static void Init() {
    ms_decl.begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::TexCoord0, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
        .end();
  }

  /**
   * @brief Sets the internal values.
   *
   * @param x The X axis position coordinate.
   * @param y The Y axis position coordinate.
   * @param z The Z axis position coordinate.
   * @param u The U axis texture coordinate.
   * @param v The V axis texture coordinate.
   * @param w The W axis texture coordinate.
   */
  void Set(float x, float y, float z, float u, float v, float w,
           ColorRGBA8 abgr) {
    x_ = x;
    y_ = y;
    z_ = z;
    u_ = u;
    v_ = v;
    w_ = w;
    abgr_ = 0xff000000 | (abgr.b << 16) | (abgr.g << 8) | abgr.r;
  }

  static bgfx::VertexDecl ms_decl;
};
}  // namespace CrossEngine

#endif  // CROSSENGINE_TEXTURE_H_
