/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_SPRITEBATCH_H_
#define CROSSENGINE_SPRITEBATCH_H_

#include <bx/math.h>

#include <vector>

#include "cross_texture.h"
#include "vertex.h"

namespace CrossEngine {
/**
 * @brief Determines how we should sort the glyphs.
 */
enum class GlyphSortType { NONE, FRONT_TO_BACK, BACK_TO_FRONT, TEXTURE };

/**
 * @brief A glyph is a single quad. These are added via SpriteBatch::draw.
 */
class Glyph {
 public:
  /**
   * @brief Construct a new Glyph object.
   */
  Glyph();

  /**
   * @brief Construct a new Glyph object.
   *
   * @param[in] dest_rect The position.
   * @param[in] uv_rect The texture UV.
   * @param[in] texture The texture.
   * @param[in] depth The depth.
   * @param[in] color The color.
   */
  Glyph(const Rect& dest_rect, const Rect& uv_rect,
        const bgfx::TextureHandle& texture, const float depth,
        const ColorRGBA8& color);

  /**
   * @brief Construct a new Glyph object.
   *
   * @param[in] dest_rect The position.
   * @param[in] uv_rect The texture UV.
   * @param[in] texture The texture.
   * @param[in] depth The depth.
   * @param[in] color The color.
   * @param[in] angle The angle.
   */
  Glyph(const Rect& dest_rect, const Rect& uv_rect,
        const bgfx::TextureHandle& texture, const float depth,
        const ColorRGBA8& color, float angle);

  bgfx::TextureHandle texture;
  float depth;

  Vertex top_left;
  Vertex bottom_left;
  Vertex top_right;
  Vertex bottom_right;

 private:
  /**
   * @brief Rotates a point about (0,0) by angle
   *
   * @param[in] position The pivot position.
   * @param[in] angle The angle
   * @return bx::Vec3 The result position.
   */
  bx::Vec3 RotatePoint(const bx::Vec3& position, float angle);
};

/**
 * @brief Class that contains render batches.
 * Each render batch is used for a single draw call
 */
class RenderBatch {
 public:
  /**
   * @brief Construct a new Render Batch object
   *
   * @param[in] offset The offset of the batch.
   * @param[in] num_vertices The number of vertices.
   * @param[in] num_indices The number of indices.
   * @param[in] texture The texture.
   */
  RenderBatch(uint32_t offset, uint32_t num_vertices, uint32_t num_indices,
              const bgfx::TextureHandle& texture)
      : offset(offset),
        num_vertices(num_vertices),
        num_indices(num_indices),
        texture(texture) {}

  uint32_t offset;
  uint32_t num_vertices;
  uint32_t num_indices;
  bgfx::TextureHandle texture;
};

/**
 * @brief Class draw sprite in batches.
 */
class SpriteBatch {
 public:
  /**
   * @brief Construct a new SpriteBatch object.
   */
  SpriteBatch();

  /**
   * @brief Destroy the SpriteBatch object.
   */
  ~SpriteBatch();

  /**
   * @brief Initializes the object.
   */
  void Init();

  /**
   * @brief Dispose the object.
   */
  void Dispose();

  /**
   * @brief Begins the spritebatch.
   *
   * @param[in] sort_type The type of glyph sort.
   */
  void Begin(GlyphSortType sort_type = GlyphSortType::TEXTURE);

  /**
   * @brief Ends the spritebatch.
   */
  void End();

  /**
   * @brief Adds a glyph to the spritebatch.
   *
   * @param[in] destination_rect The destination position.
   * @param[in] uv_rect The texture UV.
   * @param[in] texture The texture.
   * @param[in] depth The depth.
   * @param[in] color The color.
   */
  void Draw(const Rect& destination_rect, const Rect& uv_rect,
            const bgfx::TextureHandle& texture, const float depth,
            const ColorRGBA8& color);

  /**
   * @brief Adds a glyph to the spritebatch with rotation.
   *
   * @param destination_rect The destination position.
   * @param uv_rect The texture UV.
   * @param texture The texture.
   * @param depth The depth.
   * @param color The color.
   * @param angle The angle.
   */
  void Draw(const Rect& destination_rect, const Rect& uv_rect,
            const bgfx::TextureHandle& texture, const float depth,
            const ColorRGBA8& color, const float angle);

  /**
   * @brief Adds a glyph to the spritebatch with rotation.
   *
   * @param destination_rect The destination position.
   * @param uv_rect The texture UV.
   * @param texture The texture.
   * @param depth The depth.
   * @param color The color.
   * @param direction The direction.
   */
  void Draw(const Rect& destination_rect, const Rect& uv_rect,
            const bgfx::TextureHandle& texture, const float depth,
            const ColorRGBA8& color, const bx::Vec3& direction);

  /**
   * @brief Renders the entire SpriteBatch to the screen.
   */
  void RenderBatch();

 private:
  /**
   * @brief Creates all the needed RenderBatches.
   */
  void CreateRenderBatches();

  /**
   * @brief Generates our VAO and VBO.
   */
  void CreateVertexArray();

  /**
   * @brief Sorts glyphs according to sort type.
   */
  void SortGlyphs();

  /**
   * @brief Compare if one glyph depth is lower than the other.
   *
   * @param[in] a The A Glyph.
   * @param[in] b The B Glyph.
   * @return true If a depth is lower than b depth.
   * @return false If a depth is higher or equal to b depth.
   */
  static bool CompareFrontToBack(Glyph* a, Glyph* b);

  /**
   * @brief Compare if one glyph depth is highter than the other.
   *
   * @param[in] a The A Glyph.
   * @param[in] b The B Glyph.
   * @return true If a depth is higher than b depth.
   * @return false If a depth is lower or equal to b depth.
   */
  static bool CompareBackToFront(Glyph* a, Glyph* b);

  /**
   * @brief Compare if one glyph texture ID is lower than the other.
   *
   * @param[in] a The A Glyph.
   * @param[in] b The B Glyph.
   * @return true If a texture ID is lower than b depth.
   * @return false If a texture ID is higher or equal to b depth.
   */
  static bool CompareTexture(Glyph* a, Glyph* b);

  GlyphSortType sort_type_;

  std::vector<Glyph*> glyph_pointers_;
  std::vector<Glyph> glyphs_;
  std::vector<CrossEngine::RenderBatch> render_batches_;

  bgfx::TransientVertexBuffer tvb_;
  bgfx::TransientIndexBuffer tib_;
  bgfx::ProgramHandle program_;
  bgfx::UniformHandle texture_color_;
};
}  // namespace CrossEngine

#endif  // CROSSENGINE_SPRITEBATCH_H_
