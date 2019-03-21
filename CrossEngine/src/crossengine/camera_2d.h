/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_CAMERA2D_H_
#define CROSSENGINE_CAMERA2D_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace CrossEngine {
/**
 * @brief Camera class for 2D games
 */
class Camera2D {
 public:
  /**
   * @brief Construct a new Camera2D object.
   */
  Camera2D();

  /**
   * @brief Destroy the Camera2D object.
   */
  ~Camera2D();

  /**
   * @brief Sets up the orthographic matrix and screen dimensions.
   *
   * @param[in] screen_width The screen width
   * @param[in] screen_height The screen height
   */
  void Init(int screen_width, int screen_height);

  /**
   * @brief Updates the camera matrix if needed.
   */
  void Update();

  /**
   * @brief Draw the image of the camera on the screen.
   */
  void Draw();

  /**
   * @brief Convert screen coordinates to world coordinates.
   *
   * @param[in] screen_coords The screen coordinates
   * @return A glm::vec2 world coordinates.
   */
  glm::vec2 ConvertScreenToWorld(glm::vec2 screen_coords);

  /**
   * @brief Determines if box in view.
   *
   * @param[in] position The position
   * @param[in] dimensions The dimensions
   * @return True if box in view, False otherwise.
   */
  bool IsBoxInView(const glm::vec2& position, const glm::vec2& dimensions);

  /**
   * @brief Adds the offset position to the camera position
   *
   * @param[in] offset The glm::vec2 offset
   */
  void OffsetPosition(const glm::vec2& offset) {
    position_ += offset;
    needs_matrix_update_ = true;
  }

  /**
   * @brief Adds the offset scale to the camera
   *
   * @param[in] offset The offset value
   */
  void OffsetScale(float offset) {
    scale_ += offset;
    if (scale_ < 0.001f) scale_ = 0.001f;
    needs_matrix_update_ = true;
  }

  /**
   * @brief Sets the position.
   *
   * @param[in] new_position The new position
   */
  void SetPosition(const glm::vec2& new_position) {
    position_ = new_position;
    needs_matrix_update_ = true;
  }

  /**
   * \brief Sets the scale.
   *
   * \param[in] new_scale The new scale
   */
  void SetScale(float new_scale) {
    scale_ = new_scale;
    needs_matrix_update_ = true;
  }

  /**
   * @brief Gets the position.
   *
   * @return The position.
   */
  const glm::vec2& GetPosition() const { return position_; }

  /**
   * @brief Gets the scale.
   *
   * @return The scale.
   */
  float GetScale() const { return scale_; }

  /**
   * @brief Gets the camera matrix.
   *
   * @return The camera matrix.
   */
  const glm::mat4& GetCameraMatrix() const { return camera_matrix_; }

  /**
   * @brief Gets the aspect ratio.
   *
   * @return The aspect ratio.
   */
  float GetAspectRatio() const {
    return static_cast<float>(screen_width_) /
           static_cast<float>(screen_height_);
  }

 private:
  int screen_width_, screen_height_;
  bool needs_matrix_update_;
  float scale_;
  float near_;
  float far_;
  glm::vec2 position_;
  glm::mat4 camera_matrix_;
  glm::mat4 ortho_matrix_;
};
}  // namespace CrossEngine

#endif  // CROSSENGINE_CAMERA2D_H_
