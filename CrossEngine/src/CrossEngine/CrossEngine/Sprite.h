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

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "CrossTexture.h"
#include "TileSheet.h"

#include <string>

namespace CrossEngine {

/// A 2D quad that can be rendered to the screen
class Sprite {
 public:
    Sprite();
    ~Sprite();

    void SetPosition(float x, float y);
    void SetDimensions(float width, float height);

    // Initializes the sprite VBO. x, y, width, and height are
    // in the normalized device coordinate space. so, [-1, 1]
    void Init(float x, float y, float width, float height,
        CrossEngine::CrossTexture* texture);

    void Draw();

    // private:
    float m_x;
    float m_y;
    float m_width;
    float m_height;
    CrossTexture m_texture;

    bgfx::ProgramHandle m_program;
    bgfx::UniformHandle m_texColor;
    bgfx::IndexBufferHandle m_ibh;
    bgfx::VertexBufferHandle m_vbh;
};
}  // namespace CrossEngine

#endif  // _SPRITE_H_
