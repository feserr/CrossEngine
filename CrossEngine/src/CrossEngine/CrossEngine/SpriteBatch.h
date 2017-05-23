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

#ifndef _SPRITEBATCH_H_
#define _SPRITEBATCH_H_

#include "Vertex.h"

#include "../../bgfx_utils.h"

#include <glm/glm.hpp>
#include <vector>


namespace CrossEngine {
// Determines how we should sort the glyphs
enum class GlyphSortType {
    NONE,
    FRONT_TO_BACK,
    BACK_TO_FRONT,
    TEXTURE
};

// A glyph is a single quad. These are added via SpriteBatch::draw
class Glyph {
 public:
    Glyph() {
    }
    Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, 
        bgfx::TextureHandle Texture,
        float Depth, const ColorRGBA8& color);
    Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, 
        bgfx::TextureHandle Texture,
        float Depth, const ColorRGBA8& color, float angle);

    bgfx::TextureHandle texture;
    float depth;

    Vertex topLeft;
    Vertex bottomLeft;
    Vertex topRight;
    Vertex bottomRight;

 private:
    /// Rotates a point about (0,0) by angle
    glm::vec2 RotatePoint(const glm::vec2& pos, float angle);
};

// Each render batch is used for a single draw call
class RenderBatch {
 public:
    RenderBatch(unsigned int Offset, unsigned int NumVertices, 
        bgfx::TextureHandle Texture) :
        offset(Offset), numVertices(NumVertices), texture(Texture) {
    }

    unsigned int offset;
    unsigned int numVertices;
    bgfx::TextureHandle texture;
};

// The SpriteBatch class is a more efficient way of drawing sprites
class SpriteBatch {
 public:
    SpriteBatch();
    ~SpriteBatch();

    // Initializes the spritebatch
    void Init();
    void Dispose();

    // Begins the spritebatch
    void Begin(GlyphSortType sortType = GlyphSortType::TEXTURE);

    // Ends the spritebatch
    void End();

    // Adds a glyph to the spritebatch
    void Draw(const glm::vec4& destRect, const glm::vec4& uvRect,
        bgfx::TextureHandle texture, float depth, const ColorRGBA8& color);
    // Adds a glyph to the spritebatch with rotation
    void Draw(const glm::vec4& destRect, const glm::vec4& uvRect,
        bgfx::TextureHandle texture, float depth, const ColorRGBA8& color, float angle);
    // Adds a glyph to the spritebatch with rotation
    void Draw(const glm::vec4& destRect, const glm::vec4& uvRect,
        bgfx::TextureHandle texture, float depth, const ColorRGBA8& color,
        const glm::vec2& dir);

    // Renders the entire SpriteBatch to the screen
    void RenderBatch();

 private:
    // Creates all the needed RenderBatches
    void CreateRenderBatches();

    // Generates our VAO and VBO
    void CreateVertexArray();

    // Sorts glyphs according to _sortType
    void SortGlyphs();

    // Comparators used by sortGlyphs()
    static bool CompareFrontToBack(Glyph* a, Glyph* b);
    static bool CompareBackToFront(Glyph* a, Glyph* b);
    static bool CompareTexture(Glyph* a, Glyph* b);

    unsigned int m_vbo;
    unsigned int m_vao;

    GlyphSortType m_sortType;

    std::vector<Glyph*> m_glyphPointers;  ///< This is for sorting
    std::vector<Glyph> m_glyphs;  ///< These are the actual glyphs
    std::vector<CrossEngine::RenderBatch> m_renderBatches;
};
}  // namespace CrossEngine

#endif  // _SPRITEBATCH_H_
