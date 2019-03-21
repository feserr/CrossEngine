/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "crossengine/camera_2d.h"

#include <bgfx/bgfx.h>
#include <bx/math.h>
#include "entry/entry.h"

namespace CrossEngine {
Camera2D::Camera2D()
    : screen_width_(500),
      screen_height_(500),
      needs_matrix_update_(true),
      scale_(1.0f),
      near_(0.0f),
      far_(10.0f),
      position_(0.0f, 0.0f),
      camera_matrix_(1.0f),
      ortho_matrix_(1.0f) {}

Camera2D::~Camera2D() {}

void Camera2D::Init(int screenWidth, int screenHeight) {
  screen_width_ = screenWidth;
  screen_height_ = screenHeight;
  ortho_matrix_ = glm::ortho(0.0f, static_cast<float>(screen_width_), 0.0f,
                             static_cast<float>(screen_height_));
  entry::setWindowSize(entry::WindowHandle(), screenWidth, screen_height_);
}

// Updates the camera matrix if needed
void Camera2D::Update() {
  // Only update if our position or scale have changed
  if (needs_matrix_update_) {
    // Camera Translation
    glm::vec3 translate(-position_.x + screen_width_ / 2,
                        -position_.y + screen_height_ / 2, 0.0f);
    camera_matrix_ = glm::translate(ortho_matrix_, translate);

    // Camera Scale
    glm::vec3 scale(scale_, scale_, 0.0f);
    camera_matrix_ = glm::scale(glm::mat4(1.0f), scale) * camera_matrix_;

    needs_matrix_update_ = false;
  }
}

void Camera2D::Draw() {
  bgfx::setViewRect(0, 0, 0, screen_width_, screen_height_);

  const bx::Vec3 at = {0.0f, 0.0f, 0.0f};
  const bx::Vec3 eye = {0.0f, 0.0f, -5.0f};

  float view[16];
  float proj[16];
  bx::mtxLookAt(view, eye, at);

  const bgfx::Caps* caps = bgfx::getCaps();
  bx::mtxOrtho(proj, 0, screen_width_, screen_height_, 0.0f, near_, far_,
               0.0f, caps->homogeneousDepth);

  // Set view and projection matrix for view 0.
  bgfx::setViewTransform(0, view, proj);
}

glm::vec2 Camera2D::ConvertScreenToWorld(glm::vec2 screen_coords) {
  // Invert Y direction
  screen_coords.y = screen_height_ - screen_coords.y;
  // Make it so that 0 is the center
  screen_coords -= glm::vec2(screen_width_ / 2, screen_height_ / 2);
  // Scale the coordinates
  screen_coords /= scale_;
  // Translate with the camera position
  screen_coords += position_;
  return screen_coords;
}

// Simple AABB test to see if a box is in the camera view
bool Camera2D::IsBoxInView(const glm::vec2& position,
                           const glm::vec2& dimensions) {
  glm::vec2 scaledScreenDimensions =
      glm::vec2(screen_width_, screen_height_) / (scale_);

  // The minimum distance before a collision occurs
  const float MIN_DISTANCE_X =
      dimensions.x / 2.0f + scaledScreenDimensions.x / 2.0f;
  const float MIN_DISTANCE_Y =
      dimensions.y / 2.0f + scaledScreenDimensions.y / 2.0f;

  // Center position of the parameters
  glm::vec2 centerPos = position + dimensions / 2.0f;
  // Center position of the camera
  glm::vec2 centerCameraPos = position_;
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
