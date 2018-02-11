/*
    Copyright 2017-2018 Elías Serrano. All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY COPYRIGHT HOLDER ``AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
    PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER OR
    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
    OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "CrossEngine/Camera2D.h"

namespace CrossEngine {
    Camera2D::Camera2D() : m_position(0.0f, 0.0f), m_cameraMatrix(1.0f),
        m_orthoMatrix(1.0f), m_scale(1.0f), m_needsMatrixUpdate(true),
        m_screenWidth(500), m_screenHeight(500) {
    }

    Camera2D::~Camera2D() {
    }

    void Camera2D::Init(int screenWidth, int screenHeight) {
        m_screenWidth = screenWidth;
        m_screenHeight = screenHeight;
        m_orthoMatrix = glm::ortho(0.0f, static_cast<float>(m_screenWidth),
            0.0f, static_cast<float>(m_screenHeight));
    }

    // Updates the camera matrix if needed
    void Camera2D::Update() {
        // Only update if our position or scale have changed
        if (m_needsMatrixUpdate) {
            // Camera Translation
            glm::vec3 translate(-m_position.x + m_screenWidth / 2, -m_position.y
                + m_screenHeight / 2, 0.0f);
            m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

            // Camera Scale
            glm::vec3 scale(m_scale, m_scale, 0.0f);
            m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) *
                m_cameraMatrix;

            m_needsMatrixUpdate = false;
        }
    }

    glm::vec2 Camera2D::ConvertScreenToWorld(glm::vec2 screenCoords) {
        // Invert Y direction
        screenCoords.y = m_screenHeight - screenCoords.y;
        // Make it so that 0 is the center
        screenCoords -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);
        // Scale the coordinates
        screenCoords /= m_scale;
        // Translate with the camera position
        screenCoords += m_position;
        return screenCoords;
    }

    // Simple AABB test to see if a box is in the camera view
    bool Camera2D::IsBoxInView(const glm::vec2& position,
        const glm::vec2& dimensions) {
        glm::vec2 scaledScreenDimensions =
            glm::vec2(m_screenWidth, m_screenHeight) / (m_scale);

        // The minimum distance before a collision occurs
        const float MIN_DISTANCE_X = dimensions.x / 2.0f +
            scaledScreenDimensions.x / 2.0f;
        const float MIN_DISTANCE_Y = dimensions.y / 2.0f +
            scaledScreenDimensions.y / 2.0f;

        // Center position of the parameters
        glm::vec2 centerPos = position + dimensions / 2.0f;
        // Center position of the camera
        glm::vec2 centerCameraPos = m_position;
        // Vector from the input to the camera
        glm::vec2 distVec = centerPos - centerCameraPos;

        // Get the depth of the collision
        float xDepth = MIN_DISTANCE_X - std::abs(distVec.x);
        float yDepth = MIN_DISTANCE_Y - std::abs(distVec.y);

        // If both the depths are > 0, then we collided
        if (xDepth > 0 && yDepth > 0) {
            // There was a collision
            return true;
        }

        return false;
    }
}  // namespace CrossEngine
