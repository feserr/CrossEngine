/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "crossengine/sprite_batch.h"

#include <bx/uint32_t.h>

#include <algorithm>
#include <cstdio>
#include <vector>

#include "crossengine/bgfx_utils.h"

namespace CrossEngine {
bgfx::VertexLayout PosTexcoordVertex::ms_decl;

// TODO(feserr): Add emtpy constructor.

Glyph::Glyph(const Rect& dest_rect, const Rect& uv_rect,
             const bgfx::TextureHandle& texture, const float depth,
             const ColorRGBA8& color)
    : texture(texture), depth(depth) {
  top_left.color = color;
  top_left.SetPosition(dest_rect.x, dest_rect.y + dest_rect.h, depth);
  top_left.SetUV(uv_rect.x, uv_rect.y + uv_rect.h);

  bottom_left.color = color;
  bottom_left.SetPosition(dest_rect.x, dest_rect.y, depth);
  bottom_left.SetUV(uv_rect.x, uv_rect.y);

  bottom_right.color = color;
  bottom_right.SetPosition(dest_rect.x + dest_rect.w, dest_rect.y, depth);
  bottom_right.SetUV(uv_rect.x + uv_rect.w, uv_rect.y);

  top_right.color = color;
  top_right.SetPosition(dest_rect.x + dest_rect.w, dest_rect.y + dest_rect.h,
                        depth);
  top_right.SetUV(uv_rect.x + uv_rect.w, uv_rect.y + uv_rect.h);
}

Glyph::Glyph(const Rect& dest_rect, const Rect& uv_rect,
             const bgfx::TextureHandle& texture, const float depth,
             const ColorRGBA8& color, float angle)
    : texture(texture), depth(depth) {
  bx::Vec3 halfDims(dest_rect.w / 2.0f, dest_rect.h / 2.0f, 0.0f);

  // Get points centered at origin
  bx::Vec3 tl = bx::Vec3(-halfDims.x, halfDims.y, 0.0f);
  bx::Vec3 bl = bx::Vec3(-halfDims.x, -halfDims.y, 0.0f);
  bx::Vec3 br = bx::Vec3(halfDims.x, -halfDims.y, 0.0f);
  bx::Vec3 tr = bx::Vec3(halfDims.x, halfDims.y, 0.0f);

  // Rotate the points
  tl = bx::add(RotatePoint(tl, angle), halfDims);
  bl = bx::add(RotatePoint(bl, angle), halfDims);
  br = bx::add(RotatePoint(br, angle), halfDims);
  tr = bx::add(RotatePoint(tr, angle), halfDims);

  top_left.color = color;
  top_left.SetPosition(dest_rect.x + tl.x, dest_rect.y + tl.y, depth);
  top_left.SetUV(uv_rect.x, uv_rect.y + uv_rect.h);

  bottom_left.color = color;
  bottom_left.SetPosition(dest_rect.x + bl.x, dest_rect.y + bl.y, depth);
  bottom_left.SetUV(uv_rect.x, uv_rect.y);

  bottom_right.color = color;
  bottom_right.SetPosition(dest_rect.x + br.x, dest_rect.y + br.y, depth);
  bottom_right.SetUV(uv_rect.x + uv_rect.w, uv_rect.y);

  top_right.color = color;
  top_right.SetPosition(dest_rect.x + tr.x, dest_rect.y + tr.y, depth);
  top_right.SetUV(uv_rect.x + uv_rect.w, uv_rect.y + uv_rect.h);
}

bx::Vec3 Glyph::RotatePoint(const bx::Vec3& pos, float angle) {
  bx::Vec3 newv;
  newv.x = pos.x * bx::cos(angle) - pos.y * bx::sin(angle);
  newv.y = pos.x * bx::sin(angle) + pos.y * bx::cos(angle);
  return newv;
}

SpriteBatch::SpriteBatch() /* : vbo_(0), vao_(0) */ {}

SpriteBatch::~SpriteBatch() {}

void SpriteBatch::Init() { CreateVertexArray(); }

void SpriteBatch::Dispose() {
  if (bgfx::isValid(program_)) {
    bgfx::destroy(program_);
  }
  bgfx::destroy(texture_color_);
}

void SpriteBatch::Begin(GlyphSortType sort_type) {
  sort_type_ = sort_type;
  render_batches_.clear();

  // Makes m_glpyhs.size() = 0, however it does not free internal memory.
  // So when we later call emplace_back it doesn't need to internally call new.
  glyphs_.clear();
}

void SpriteBatch::End() {
  // Set up all pointers for fast sorting
  glyph_pointers_.resize(glyphs_.size());
  for (size_t i = 0; i < glyphs_.size(); i++) {
    glyph_pointers_[i] = &glyphs_[i];
  }

  SortGlyphs();
  CreateRenderBatches();
}

void SpriteBatch::Draw(const Rect& dest_rect, const Rect& uv_rect,
                       const bgfx::TextureHandle& texture, const float depth,
                       const ColorRGBA8& color) {
  glyphs_.emplace_back(dest_rect, uv_rect, texture, depth, color);
}

void SpriteBatch::Draw(const Rect& dest_rect, const Rect& uv_rect,
                       const bgfx::TextureHandle& texture, const float depth,
                       const ColorRGBA8& color, const float angle) {
  glyphs_.emplace_back(dest_rect, uv_rect, texture, depth, color, angle);
}

void SpriteBatch::Draw(const Rect& dest_rect, const Rect& uv_rect,
                       const bgfx::TextureHandle& texture, const float depth,
                       const ColorRGBA8& color, const bx::Vec3& dir) {
  const bx::Vec3 right = bx::Vec3(1.0f, 0.0f, 0.0f);
  float angle = bx::acos(bx::dot(right, dir));
  if (dir.y < 0.0f) angle = -angle;

  glyphs_.emplace_back(dest_rect, uv_rect, texture, depth, color, angle);
}

void SpriteBatch::RenderBatch() {
  // Set render states.
  bgfx::setState(0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A |
                 BGFX_STATE_DEPTH_TEST_LESS | BGFX_STATE_CULL_CW |
                 BGFX_STATE_BLEND_NORMAL);

  for (size_t i = 0; i < render_batches_.size(); i++) {
    bgfx::setVertexBuffer(0, &tvb_, render_batches_[i].offset,
                          render_batches_[i].num_vertices);
    bgfx::setIndexBuffer(&tib_, render_batches_[i].offset,
                         render_batches_[i].num_indices);

    // Bind texture.
    bgfx::setTexture(0, texture_color_, render_batches_[i].texture);
  }

  // Submit primitive for rendering to view 0.
  bgfx::submit(0, program_);
  bgfx::submit(1, program_);
}

void SpriteBatch::CreateRenderBatches() {
  if (glyph_pointers_.empty()) {
    return;
  }

  const uint32_t num = static_cast<uint32_t>(glyphs_.size());

  const uint32_t numVertices =
      bgfx::getAvailTransientVertexBuffer(num * 4, PosTexcoordVertex::ms_decl);
  const uint32_t numIndices = bgfx::getAvailTransientIndexBuffer(num * 6);
  const uint32_t max = bx::uint32_min(numVertices / 4, numIndices / 6);

  bgfx::allocTransientBuffers(&tvb_, PosTexcoordVertex::ms_decl, max * 4, &tib_,
                              max * 6);

  PosTexcoordVertex* vertices = reinterpret_cast<PosTexcoordVertex*>(tvb_.data);
  PosTexcoordVertex* vertex = &vertices[0];
  Glyph* g = glyph_pointers_[0];

  int offset = 0;  // current offset

  // Add the first batch
  render_batches_.emplace_back(offset, 4, 6, glyph_pointers_[0]->texture);
  vertex->Set(g->top_left.position.x, g->top_left.position.y,
              g->top_left.position.z, g->top_left.uv.u, g->top_left.uv.v, 0.0f,
              g->top_left.color);
  ++vertex;

  vertex->Set(g->top_right.position.x, g->top_right.position.y,
              g->top_right.position.z, g->top_right.uv.u, g->top_right.uv.v,
              0.0f, g->top_right.color);
  ++vertex;

  vertex->Set(g->bottom_left.position.x, g->bottom_left.position.y,
              g->bottom_left.position.z, g->bottom_left.uv.u,
              g->bottom_left.uv.v, 0.0f, g->bottom_left.color);
  ++vertex;

  vertex->Set(g->bottom_right.position.x, g->bottom_right.position.y,
              g->bottom_right.position.z, g->bottom_right.uv.u,
              g->bottom_right.uv.v, 0.0f, g->bottom_right.color);
  ++vertex;
  offset += 4;

  // Add all the rest of the glyphs
  for (size_t cg = 1; cg < glyph_pointers_.size(); cg++) {
    // Check if this glyph can be part of the current batch
    if (glyph_pointers_[cg]->texture.idx !=
        glyph_pointers_[cg - 1]->texture.idx) {
      // Make a new batch
      render_batches_.emplace_back(offset, 4, 6, glyph_pointers_[cg]->texture);
    } else {
      // If its part of the current batch increase numVertices
      render_batches_.back().num_vertices += 4;
      render_batches_.back().num_indices += 6;
    }
    vertex = &vertices[cg * 4];
    g = glyph_pointers_[cg];

    vertex->Set(g->top_left.position.x, g->top_left.position.y,
                g->top_left.position.z, g->top_left.uv.u, g->top_left.uv.v,
                0.0f, g->top_left.color);
    ++vertex;

    vertex->Set(g->top_right.position.x, g->top_right.position.y,
                g->top_right.position.z, g->top_right.uv.u, g->top_right.uv.v,
                0.0f, g->top_right.color);
    ++vertex;

    vertex->Set(g->bottom_left.position.x, g->bottom_left.position.y,
                g->bottom_left.position.z, g->bottom_left.uv.u,
                g->bottom_left.uv.v, 0.0f, g->bottom_left.color);
    ++vertex;

    vertex->Set(g->bottom_right.position.x, g->bottom_right.position.y,
                g->bottom_right.position.z, g->bottom_right.uv.u,
                g->bottom_right.uv.v, 0.0f, g->bottom_right.color);
    ++vertex;

    offset += 4;
  }

  uint16_t* indices = reinterpret_cast<uint16_t*>(tib_.data);
  for (uint32_t ii = 0; ii < num; ++ii) {
    uint16_t* index = &indices[ii * 6];
    index[0] = ii * 4 + 0;  // 0
    index[1] = ii * 4 + 1;  // 1
    index[2] = ii * 4 + 2;  // 2
    index[3] = ii * 4 + 1;  // 1
    index[4] = ii * 4 + 3;  // 3
    index[5] = ii * 4 + 2;  // 2
  }
}

void SpriteBatch::CreateVertexArray() {
  // Create vertex stream declaration.
  PosTexcoordVertex::Init();

  // Create program from shaders.
  program_ = loadProgram("vs_texture_shading", "fs_texture_shading");

  texture_color_ =
      bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
}

void SpriteBatch::SortGlyphs() {
  switch (sort_type_) {
    case GlyphSortType::BACK_TO_FRONT:
      std::stable_sort(glyph_pointers_.begin(), glyph_pointers_.end(),
                       CompareBackToFront);
      break;
    case GlyphSortType::FRONT_TO_BACK:
      std::stable_sort(glyph_pointers_.begin(), glyph_pointers_.end(),
                       CompareFrontToBack);
      break;
    case GlyphSortType::TEXTURE:
      std::stable_sort(glyph_pointers_.begin(), glyph_pointers_.end(),
                       CompareTexture);
      break;
    case GlyphSortType::NONE:
    default:
      break;
  }
}

bool SpriteBatch::CompareFrontToBack(Glyph* a, Glyph* b) {
  return (a->depth < b->depth);
}

bool SpriteBatch::CompareBackToFront(Glyph* a, Glyph* b) {
  return (a->depth > b->depth);
}

bool SpriteBatch::CompareTexture(Glyph* a, Glyph* b) {
  return (a->texture.idx < b->texture.idx);
}
}  // namespace CrossEngine
