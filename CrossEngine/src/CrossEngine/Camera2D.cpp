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
