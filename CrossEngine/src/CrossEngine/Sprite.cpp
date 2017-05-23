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

#include <string>
#include <cstddef>

namespace CrossEngine {
    Sprite::Sprite() {
        m_vboID = 0;
    }


    Sprite::~Sprite() {
        // Always remember to delete your buffers when
        // you are done!
        if (m_vboID != 0) {
            //glDeleteBuffers(1, &m_vboID);
        }
    }

    // Initializes the sprite VBO. x, y, width, and height are
    // in the normalized device coordinate space. so, [-1, 1]
    void Sprite::Init(float x, float y, float width, float height,
        std::string texturePath) {
        // Set up our private vars
        m_x = x;
        m_y = y;
        m_width = width;
        m_height = height;

        m_texture = ResourceManager::GetTexture(texturePath);

        // Generate the buffer if it hasn't already been generated
        if (m_vboID == 0) {
            //glGenBuffers(1, &m_vboID);
        }

        // This array will hold our vertex data.
        // We need 6 vertices, and each vertex has 2
        // floats for X and Y
        Vertex vertexData[6];

        // First Triangle
        vertexData[0].SetPosition(x + width, y + height);
        vertexData[0].SetUV(1.0f, 1.0f);

        vertexData[1].SetPosition(x, y + height);
        vertexData[1].SetUV(0.0f, 1.0f);

        vertexData[2].SetPosition(x, y);
        vertexData[2].SetUV(0.0f, 0.0f);

        // Second Triangle
        vertexData[3].SetPosition(x, y);
        vertexData[3].SetUV(0.0f, 0.0f);

        vertexData[4].SetPosition(x + width, y);
        vertexData[4].SetUV(1.0f, 0.0f);

        vertexData[5].SetPosition(x + width, y + height);
        vertexData[5].SetUV(1.0f, 1.0f);

        // Set all vertex colors to magenta
        for (int i = 0; i < 6; i++) {
            vertexData[4].SetColor(255, 0, 255, 255);
        }

        vertexData[4].SetColor(0, 0, 255, 255);

        vertexData[4].SetColor(0, 255, 0, 255);


        // Tell opengl to bind our vertex buffer object
        /*glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
        // Upload the data to the GPU
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData,
            GL_STATIC_DRAW);

        // Unbind the buffer (optional)
        glBindBuffer(GL_ARRAY_BUFFER, 0);*/
    }

    // Draws the sprite to the screen
    void Sprite::Draw() {
        /*glBindTexture(GL_TEXTURE_2D, m_texture.id);

        // Bind the buffer object
        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

        // Tell opengl what attribute arrays we need
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        // This is the position attribute pointer
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            reinterpret_cast<void*>(offsetof(Vertex, position)));
        // This is the UV attribute pointer
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            reinterpret_cast<void*>(offsetof(Vertex, uv)));
        // This is the color attribute pointer
        glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex),
            reinterpret_cast<void*>(offsetof(Vertex, color)));


        // Draw the 6 vertices to the screen
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Disable the vertex attrib arrays. This is not optional.
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        // Unbind the VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);*/
    }
}  // namespace CrossEngine
