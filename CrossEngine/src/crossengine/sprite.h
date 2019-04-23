/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_SPRITE_H_
#define CROSSENGINE_SPRITE_H_

#include <string>
#include "cross_texture.h"
#include "tile_sheet.h"

namespace CrossEngine {

/**
 * @brief A 2D quad that can be rendered to the screen
 */
class Sprite {
 public:
  /**
   * @brief Construct a new Sprite object.
   */
  Sprite();

  /**
   * @brief Destroy the Sprite object.
   */
  ~Sprite();

  /**
   * @brief Set the position object.
   *
   * @param[in] x The X axis position.
   * @param[in] y The Y axis position.
   */
  void SetPosition(float x, float y);

  /**
   * @brief Set the dimensions object.
   *
   * @param[in] width The width.
   * @param[in] height The height.
   */
  void SetDimensions(float width, float height);

  /**
   * @brief Initializes the sprite.
   * VBO, x, y, width, and height are in the
   * normalized device coordinate space. so, [-1, 1]
   *
   * @param[in] x The X axis position.
   * @param[in] y The Y axis position.
   * @param[in] width The width.
   * @param[in] height The height.
   * @param[in] texture The texture.
   */
  void Init(float x, float y, float width, float height,
            CrossEngine::CrossTexture* texture);

  /**
   * @brief Render the sprite to the screen.
   */
  void Draw();

 private:
  float x_;
  float y_;
  float width_;
  float height_;
  CrossTexture texture_;

  bgfx::ProgramHandle program_;
  bgfx::UniformHandle texture_color_;
  bgfx::IndexBufferHandle ibh_;
  bgfx::VertexBufferHandle vbh_;
};
}  // namespace CrossEngine

#endif  // CROSSENGINE_SPRITE_H_
