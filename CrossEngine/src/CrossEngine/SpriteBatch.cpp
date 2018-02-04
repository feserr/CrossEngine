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

    static PosTexcoordVertex m_cubeVertices[4] =
    {
        {-1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  0.0f },
        { 1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  0.0f },
        {-1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  0.0f },
        { 1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  0.0f },
    };

    static const uint16_t m_cubeIndices[6] =
    {
        0,  1,  2, // 0
        1,  3,  2,
    };


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
        bgfx::destroy(m_ibh);
        bgfx::destroy(m_vbh);
        if (bgfx::isValid(m_program) )
        {
            bgfx::destroy(m_program);
        }
        bgfx::destroy(m_texColor);
    }

    void SpriteBatch::Init() {
        CreateVertexArray();
    }

    void SpriteBatch::Dispose() {
        if (m_vao != 0) {
            //glDeleteVertexArrays(1, &m_vao);
            m_vao = 0;
        }
        if (m_vbo != 0) {
            //glDeleteBuffers(1, &m_vbo);
            m_vbo = 0;
        }
    }

    void SpriteBatch::Begin(GlyphSortType sortType) {
        m_sortType = sortType;
        m_renderBatches.clear();

        // Makes m_glpyhs.size() == 0, however it does not free internal memory.
        // So when we later call emplace_back it doesn't need to internally call
        // new.
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
        float mtx[16];
        for (size_t i = 0; i < m_glyphs.size(); i++) {
            bx::mtxTranslate(mtx,
                m_glyphs[i].bottomLeft.position.x,
                m_glyphs[i].bottomLeft.position.y,
                0.0f);

            // Set model matrix for rendering.
            bgfx::setTransform(mtx);

            m_cubeVertices[0] = {
                m_glyphs[i].topLeft.position.x, m_glyphs[i].topLeft.position.y,
                1.0f,
                m_glyphs[i].topLeft.uv.u, m_glyphs[i].topLeft.uv.v, 0.0f };
            m_cubeVertices[1] = {
                m_glyphs[i].topRight.position.x, m_glyphs[i].topRight.position.y,
                1.0f,
                m_glyphs[i].topRight.uv.u, m_glyphs[i].topRight.uv.v, 0.0f };
            m_cubeVertices[2] = {
                m_glyphs[i].bottomLeft.position.x, m_glyphs[i].bottomLeft.position.y,
                1.0f,
                m_glyphs[i].bottomLeft.uv.u, m_glyphs[i].bottomLeft.uv.v, 0.0f };
            m_cubeVertices[3] = {
                m_glyphs[i].bottomRight.position.x, m_glyphs[i].bottomRight.position.y,
                1.0f,
                m_glyphs[i].bottomRight.uv.u, m_glyphs[i].bottomRight.uv.v, 0.0f };

            // Set vertex and index buffer.
            bgfx::setVertexBuffer(0, m_vbh);
            bgfx::setIndexBuffer(m_ibh);

            // Bind texture.
            bgfx::setTexture(0, m_texColor, m_glyphs[i].texture);

            // Set render states.
            bgfx::setState(BGFX_STATE_DEFAULT);

            // Submit primitive for rendering to view 1.
            bgfx::submit(0, m_program);
        }
    }

    void SpriteBatch::CreateRenderBatches() {
        // This will store all the vertices that we need to upload
        std::vector <Vertex> vertices;
        // Resize the buffer to the exact size we need so we can treat
        // it like an array
        vertices.resize(m_glyphPointers.size() * 6);

        if (m_glyphPointers.empty()) {
            return;
        }

        int offset = 0;  // current offset
        int cv = 0;  // current vertex

        // Add the first batch
        m_renderBatches.emplace_back(offset, 6, m_glyphPointers[0]->texture);
        vertices[cv++] = m_glyphPointers[0]->topLeft;
        vertices[cv++] = m_glyphPointers[0]->bottomLeft;
        vertices[cv++] = m_glyphPointers[0]->bottomRight;
        vertices[cv++] = m_glyphPointers[0]->bottomRight;
        vertices[cv++] = m_glyphPointers[0]->topRight;
        vertices[cv++] = m_glyphPointers[0]->topLeft;
        offset += 6;

        // Add all the rest of the glyphs
        for (size_t cg = 1; cg < m_glyphPointers.size(); cg++) {
            // Check if this glyph can be part of the current batch
            if (m_glyphPointers[cg]->texture.idx !=
                m_glyphPointers[cg - 1]->texture.idx) {
                // Make a new batch
                m_renderBatches.emplace_back(offset, 6,
                    m_glyphPointers[cg]->texture);
            } else {
                // If its part of the current batch, just increase numVertices
                m_renderBatches.back().numVertices += 6;
            }
            vertices[cv++] = m_glyphPointers[cg]->topLeft;
            vertices[cv++] = m_glyphPointers[cg]->bottomLeft;
            vertices[cv++] = m_glyphPointers[cg]->bottomRight;
            vertices[cv++] = m_glyphPointers[cg]->bottomRight;
            vertices[cv++] = m_glyphPointers[cg]->topRight;
            vertices[cv++] = m_glyphPointers[cg]->topLeft;
            offset += 6;
        }
    }

    void SpriteBatch::CreateVertexArray() {
        // Create vertex stream declaration.
        PosTexcoordVertex::init();

        // Create static vertex buffer.
        m_vbh = bgfx::createVertexBuffer(bgfx::makeRef(m_cubeVertices, sizeof(m_cubeVertices) ), PosTexcoordVertex::ms_decl);

        // Create static index buffer.
        m_ibh = bgfx::createIndexBuffer(bgfx::makeRef(m_cubeIndices, sizeof(m_cubeIndices) ) );

        // Create program from shaders.
        m_program = loadProgram("vs_update", "fs_update_cmp");

        m_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Int1);
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
