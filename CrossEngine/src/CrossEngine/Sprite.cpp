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

#include "CrossEngine/Sprite.h"
#include "CrossEngine/Vertex.h"
#include "CrossEngine/ResourceManager.h"

#include "../common/bgfx_utils.h"

#include <string>
#include <cstddef>

namespace CrossEngine {

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

Sprite::Sprite() : m_x(0.0f), m_y(0.0f), m_width(0.0f), m_height(0.0f),
    m_texture(CrossTexture()){
}

Sprite::~Sprite() {
    if (bgfx::isValid(m_texture.texture)) {
        bgfx::destroy(m_texture.texture);
    }
    bgfx::destroy(m_ibh);
    bgfx::destroy(m_vbh);
    if (bgfx::isValid(m_program) )
    {
        bgfx::destroy(m_program);
    }
    bgfx::destroy(m_texColor);
}

void Sprite::SetPosition(float x, float y) {
    m_x = x;
    m_y = y;
}

void Sprite::SetDimensions(float width, float height) {
    m_width = width;
    m_height = height;
}

void Sprite::Init(float x, float y, float width, float height,
    CrossEngine::CrossTexture* texture) {
    // Set up our private vars
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;

    m_texture = *texture;

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

// Draws the sprite to the screen
void Sprite::Draw() {
    float mtx[16];
    bx::mtxTranslate(mtx, m_x, m_y, 0.0f);

    // Set model matrix for rendering.
    bgfx::setTransform(mtx);

    // Set vertex and index buffer.
    bgfx::setVertexBuffer(0, m_vbh);
    bgfx::setIndexBuffer(m_ibh);

    // Bind texture.
    bgfx::setTexture(0, m_texColor, m_texture.texture);

    // Set render states.
    bgfx::setState(BGFX_STATE_DEFAULT);

    // Submit primitive for rendering to view 1.
    bgfx::submit(0, m_program);
}
}
