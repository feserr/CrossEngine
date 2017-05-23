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

#ifndef _CAMERA2D_H_
#define _CAMERA2D_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace CrossEngine {
/// Camera class for 2D games
class Camera2D {
 public:
    Camera2D();
    ~Camera2D();
    
    /**
     * \brief      Sets up the orthographic matrix and screen dimensions.
     *
     * \param[in]  screenWidth   The screen width
     * \param[in]  screenHeight  The screen height
     */
    void Init(int screenWidth, int screenHeight);

    /// Updates the camera matrix if needed
    void Update();

    /**
     * \brief      Convert screen coordinates to world coordinates.
     *
     * \param[in]  screenCoords  The screen coordinates
     *
     * \return     A glm::vec2 world coordinates.
     */
    glm::vec2 ConvertScreenToWorld(glm::vec2 screenCoords);

    /**
     * \brief      Determines if box in view.
     *
     * \param[in]  position    The position
     * \param[in]  dimensions  The dimensions
     *
     * \return     True if box in view, False otherwise.
     */
    bool IsBoxInView(const glm::vec2& position, const glm::vec2& dimensions);

    /**
     * \brief      Adds the offset position to the camera position
     *
     * \param[in]  offset  The glm::vec2 offset
     */
    void OffsetPosition(const glm::vec2& offset) {
        m_position += offset;
        m_needsMatrixUpdate = true;
    }

    /**
     * \brief      Adds the offset scale to the camera
     *
     * \param[in]  offset  The offset value
     */
    void OffsetScale(float offset) {
        m_scale += offset;
        if (m_scale < 0.001f)
            m_scale = 0.001f;
        m_needsMatrixUpdate = true;
    }

    /**
     * \brief      Sets the position.
     *
     * \param[in]  newPosition  The new position
     */
    void SetPosition(const glm::vec2& newPosition) {
        m_position = newPosition;
        m_needsMatrixUpdate = true;
    }

    /**
     * \brief      Sets the scale.
     *
     * \param[in]  newScale  The new scale
     */
    void SetScale(float newScale) {
        m_scale = newScale;
    m_needsMatrixUpdate = true;
    }

    /**
     * \brief      Gets the position.
     *
     * \return     The position.
     */
    const glm::vec2& GetPosition() const { return m_position; }
    
    /**
     * \brief      Gets the scale.
     *
     * \return     The scale.
     */
    float GetScale() const { return m_scale; }
    
    /**
     * \brief      Gets the camera matrix.
     *
     * \return     The camera matrix.
     */
    const glm::mat4& GetCameraMatrix() const { return m_cameraMatrix; }
    
    /**
     * \brief      Gets the aspect ratio.
     *
     * \return     The aspect ratio.
     */
    float GetAspectRatio() const {
        return static_cast<float>(m_screenWidth) /
            static_cast<float>(m_screenHeight);
    }

 private:
    int m_screenWidth, m_screenHeight;
    bool m_needsMatrixUpdate;
    float m_scale;
    glm::vec2 m_position;
    glm::mat4 m_cameraMatrix;
    glm::mat4 m_orthoMatrix;
};
}  // namespace CrossEngine

#endif  // _CAMERA2D_H_
