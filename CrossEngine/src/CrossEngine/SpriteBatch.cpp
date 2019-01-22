/*
    Copyright [2016] [Elías Serrano]

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "CrossEngine/SpriteBatch.h"

#include <vector>
#include <algorithm>
#include <cstdio>

namespace CrossEngine {
    bgfx::VertexDecl PosTexcoordVertex::ms_decl;

    Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect,
        bgfx::TextureHandle Texture, float Depth, const ColorRGBA8& color) :
        texture(Texture), depth(Depth) {
        topLeft.color = color;
        topLeft.SetPosition(destRect.x, destRect.y + destRect.w);
        topLeft.SetUV(uvRect.x, uvRect.y + uvRect.w);

        bottomLeft.color = color;
        bottomLeft.SetPosition(destRect.x, destRect.y);
        bottomLeft.SetUV(uvRect.x, uvRect.y);

        bottomRight.color = color;
        bottomRight.SetPosition(destRect.x + destRect.z, destRect.y);
        bottomRight.SetUV(uvRect.x + uvRect.z, uvRect.y);

        topRight.color = color;
        topRight.SetPosition(destRect.x + destRect.z, destRect.y + destRect.w);
        topRight.SetUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
    }

    Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect,
        bgfx::TextureHandle Texture, float Depth, const ColorRGBA8& color, float angle) :
        texture(Texture), depth(Depth) {
        glm::vec2 halfDims(destRect.z / 2.0f, destRect.w / 2.0f);

        // Get points centered at origin
        glm::vec2 tl(-halfDims.x, halfDims.y);
        glm::vec2 bl(-halfDims.x, -halfDims.y);
        glm::vec2 br(halfDims.x, -halfDims.y);
        glm::vec2 tr(halfDims.x, halfDims.y);

        // Rotate the points
        tl = RotatePoint(tl, angle) + halfDims;
        bl = RotatePoint(bl, angle) + halfDims;
        br = RotatePoint(br, angle) + halfDims;
        tr = RotatePoint(tr, angle) + halfDims;

        topLeft.color = color;
        topLeft.SetPosition(destRect.x + tl.x, destRect.y + tl.y);
        topLeft.SetUV(uvRect.x, uvRect.y + uvRect.w);

        bottomLeft.color = color;
        bottomLeft.SetPosition(destRect.x + bl.x, destRect.y + bl.y);
        bottomLeft.SetUV(uvRect.x, uvRect.y);

        bottomRight.color = color;
        bottomRight.SetPosition(destRect.x + br.x, destRect.y + br.y);
        bottomRight.SetUV(uvRect.x + uvRect.z, uvRect.y);

        topRight.color = color;
        topRight.SetPosition(destRect.x + tr.x, destRect.y + tr.y);
        topRight.SetUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
    }

    glm::vec2 Glyph::RotatePoint(const glm::vec2& pos, float angle) {
        glm::vec2 newv;
        newv.x = pos.x * cos(angle) - pos.y * sin(angle);
        newv.y = pos.x * sin(angle) + pos.y * cos(angle);
        return newv;
    }

    SpriteBatch::SpriteBatch() : m_vbo(0), m_vao(0) {
    }

    SpriteBatch::~SpriteBatch() {
    }

    void SpriteBatch::Init() {
        CreateVertexArray();
    }

    void SpriteBatch::Dispose() {
        if (bgfx::isValid(m_program) )
        {
            bgfx::destroy(m_program);
        }
        bgfx::destroy(m_texColor);
    }

    void SpriteBatch::Begin(GlyphSortType sortType) {
        m_sortType = sortType;
        m_renderBatches.clear();

        // Makes m_glpyhs.size() == 0, however it does not free
        // internal memory.
        // So when we later call emplace_back it doesn't need to
        // internally call new.
        m_glyphs.clear();
    }

    void SpriteBatch::End() {
        // Set up all pointers for fast sorting
        m_glyphPointers.resize(m_glyphs.size());
        for (size_t i = 0; i < m_glyphs.size(); i++) {
            m_glyphPointers[i] = &m_glyphs[i];
        }

        SortGlyphs();
        CreateRenderBatches();
    }

    void SpriteBatch::Draw(const glm::vec4& destRect, const glm::vec4& uvRect,
        bgfx::TextureHandle texture, float depth, const ColorRGBA8& color) {
        m_glyphs.emplace_back(destRect, uvRect, texture, depth, color);
    }

    void SpriteBatch::Draw(const glm::vec4& destRect, const glm::vec4& uvRect,
        bgfx::TextureHandle texture, float depth, const ColorRGBA8& color, float angle) {
        m_glyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);
    }

    void SpriteBatch::Draw(const glm::vec4& destRect, const glm::vec4& uvRect,
        bgfx::TextureHandle texture, float depth, const ColorRGBA8& color,
        const glm::vec2& dir) {
        const glm::vec2 right(1.0f, 0.0f);
        float angle = acos(glm::dot(right, dir));
        if (dir.y < 0.0f)
            angle = -angle;

        m_glyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);
    }

    void SpriteBatch::RenderBatch() {
        // Set render states.
        bgfx::setState(0
            | BGFX_STATE_WRITE_RGB
            | BGFX_STATE_WRITE_A
            | BGFX_STATE_DEPTH_TEST_LESS
            | BGFX_STATE_CULL_CW
            | BGFX_STATE_BLEND_NORMAL);

        for (size_t i = 0; i < m_renderBatches.size(); i++) {
            bgfx::setVertexBuffer(0, &m_tvb, m_renderBatches[i].offset,
                m_renderBatches[i].numVertices);
            bgfx::setIndexBuffer(&m_tib, m_renderBatches[i].offset,
                m_renderBatches[i].numIndices);

            // Bind texture.
            bgfx::setTexture(0, m_texColor,
                m_renderBatches[i].texture);
        }

        // Submit primitive for rendering to view 1.
        bgfx::submit(0, m_program);
    }

    void SpriteBatch::CreateRenderBatches() {
        if (m_glyphPointers.empty()) {
            return;
        }

        const uint32_t num = static_cast<uint32_t>(m_glyphs.size());

        const uint32_t numVertices =
        bgfx::getAvailTransientVertexBuffer(num * 4,
            PosTexcoordVertex::ms_decl);
        const uint32_t numIndices = bgfx::getAvailTransientIndexBuffer(num * 6);
        const uint32_t max = bx::uint32_min(numVertices / 4, numIndices / 6);

        bgfx::allocTransientBuffers(
            &m_tvb, PosTexcoordVertex::ms_decl, max * 4,
            &m_tib, max * 6);

        PosTexcoordVertex* vertices = (PosTexcoordVertex*)m_tvb.data;
        PosTexcoordVertex* vertex = &vertices[0];
        Glyph* g = m_glyphPointers[0];

        int offset = 0;  // current offset

        // Add the first batch
        m_renderBatches.emplace_back(offset, 4, 6,
            m_glyphPointers[0]->texture);
        vertex->set (
             g->topLeft.position.x, g->topLeft.position.y, 1.0f,
             g->topLeft.uv.u, g->topLeft.uv.v, 0.0f);
        ++vertex;

        vertex->set(
            g->topRight.position.x, g->topRight.position.y, 1.0f,
            g->topRight.uv.u, g->topRight.uv.v, 0.0f);
        ++vertex;

        vertex->set(
            g->bottomLeft.position.x, g->bottomLeft.position.y, 1.0f,
            g->bottomLeft.uv.u, g->bottomLeft.uv.v, 0.0f);
        ++vertex;

        vertex->set(
            g->bottomRight.position.x, g->bottomRight.position.y, 1.0f,
            g->bottomRight.uv.u, g->bottomRight.uv.v, 0.0f);
        ++vertex;
        offset += 4;

        // Add all the rest of the glyphs
        for (size_t cg = 1; cg < m_glyphPointers.size(); cg++) {
            // Check if this glyph can be part of the current batch
            if (m_glyphPointers[cg]->texture.idx !=
                m_glyphPointers[cg - 1]->texture.idx) {
                // Make a new batch
                m_renderBatches.emplace_back(offset, 4, 6,
                    m_glyphPointers[cg]->texture);
            } else {
                // If its part of the current batch increase numVertices
                m_renderBatches.back().numVertices += 4;
                m_renderBatches.back().numIndices += 6;
            }
            vertex = &vertices[cg * 4];
            g = m_glyphPointers[cg];

            vertex->set (
                g->topLeft.position.x, g->topLeft.position.y, 1.0f,
                g->topLeft.uv.u, g->topLeft.uv.v, 0.0f);
            ++vertex;

            vertex->set(
                g->topRight.position.x, g->topRight.position.y, 1.0f,
                g->topRight.uv.u, g->topRight.uv.v, 0.0f);
            ++vertex;

            vertex->set(
                g->bottomLeft.position.x, g->bottomLeft.position.y, 1.0f,
                g->bottomLeft.uv.u, g->bottomLeft.uv.v, 0.0f);
            ++vertex;

            vertex->set(
                g->bottomRight.position.x, g->bottomRight.position.y, 1.0f,
                g->bottomRight.uv.u, g->bottomRight.uv.v, 0.0f);
            ++vertex;

            offset += 4;
        }

        uint16_t* indices = (uint16_t*)m_tib.data;
        for (uint32_t ii = 0; ii < num; ++ii) {
            uint16_t* index = &indices[ii * 6];
            index[0] = ii*4+0;
            index[1] = ii*4+1;
            index[2] = ii*4+2;
            index[3] = ii*4+1;
            index[4] = ii*4+3;
            index[5] = ii*4+2;
        }
    }

    void SpriteBatch::CreateVertexArray() {
        // Create vertex stream declaration.
        PosTexcoordVertex::init();

        // Create program from shaders.
        m_program = loadProgram("vs_update", "fs_update_cmp");

        m_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
    }

    void SpriteBatch::SortGlyphs() {
        switch (m_sortType) {
            case GlyphSortType::BACK_TO_FRONT:
                std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(),
                    CompareBackToFront);
                break;
            case GlyphSortType::FRONT_TO_BACK:
                std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(),
                    CompareFrontToBack);
                break;
            case GlyphSortType::TEXTURE:
                std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(),
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
