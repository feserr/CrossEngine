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

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../../common/bgfx_utils.h"

#include <string>

namespace CrossEngine {
/// An OpenGL texture info.
struct CrossTexture {
    std::string filePath = "";  ///< The filepath to the texture
    bgfx::TextureHandle texture;  ///< The texture
    int width;  ///< The width
    int height;  ///< The height
};

struct PosTexcoordVertex {
    float m_x;
    float m_y;
    float m_z;
    float m_u;
    float m_v;
    float m_w;

    static void init() {
        ms_decl
        .begin()
        .add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::TexCoord0, 3, bgfx::AttribType::Float)
        .end();
    };

    void set(float x, float y, float z, float u, float v, float w) {
        m_x = x;
        m_y = y;
        m_z = z;
        m_u = u;
        m_v = v;
        m_w = w;
    }

    static bgfx::VertexDecl ms_decl;
};
}  // namespace CrossEngine

#endif  // _TEXTURE_H_
