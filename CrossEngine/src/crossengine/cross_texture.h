/*
 * Copyright 2020 Elías Serrano. All rights reserved.
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
  std::string file_path;        ///< The filepath to the texture
  bgfx::TextureHandle texture;  ///< The texture
  int width;                    ///< The width
  int height;                   ///< The height
};

/**
 * @brief A struct contaning position, texture coordinates and vertex. Useful
 * for shaders.
 */
struct PosTexcoordVertex {
  float x;
  float y;
  float z;
  float u;
  float v;
  float w;
  uint32_t abgr;

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
   * @param[in] _x The X axis position coordinate.
   * @param[in] _y The Y axis position coordinate.
   * @param[in] _z The Z axis position coordinate.
   * @param[in] _u The U axis texture coordinate.
   * @param[in] _v The V axis texture coordinate.
   * @param[in] _w The W axis texture coordinate.
   */
  void Set(float _x, float _y, float _z, float _u, float _v, float _w,
           ColorRGBA8 _abgr) {
    x = _x;
    y = _y;
    z = _z;
    u = _u;
    v = _v;
    w = _w;
    abgr = 0xff000000 | (_abgr.b << 16) | (_abgr.g << 8) | _abgr.r;
  }

  static bgfx::VertexLayout ms_decl;
};
}  // namespace CrossEngine

#endif  // CROSSENGINE_TEXTURE_H_
