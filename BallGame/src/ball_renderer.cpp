/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "ball_renderer.h"

#include <crossengine/cpp_utils.h>

#include <glm/glm.hpp>

BallRenderer::~BallRenderer() {}

void BallRenderer::RenderBalls(CrossEngine::SpriteBatch* sprite_batch,
                               const std::vector<Ball>& balls) {
  sprite_batch->Begin();

  // Render all the balls
  for (auto& ball : balls) {
    const CrossEngine::Rect uv_rect = {-1.0f, -1.0f, 2.0f, 2.0f};
    const CrossEngine::Rect dest_rect = {
        ball.position.x - ball.radius, ball.position.y - ball.radius,
        ball.radius * 2.0f, ball.radius * 2.0f};
    sprite_batch->Draw(dest_rect, uv_rect, ball.texture.texture,
                       ball.position.z, ball.color);
  }

  sprite_batch->End();
  sprite_batch->RenderBatch();
}

MomentumBallRenderer::~MomentumBallRenderer() {}

void MomentumBallRenderer::RenderBalls(CrossEngine::SpriteBatch* sprite_batch,
                                       const std::vector<Ball>& balls) {
  sprite_batch->Begin();

  // Render all the balls
  for (auto& ball : balls) {
    const CrossEngine::Rect uv_rect = {-1.0f, -1.0f, 2.0f, 2.0f};
    const CrossEngine::Rect dest_rect = {
        ball.position.x - ball.radius, ball.position.y - ball.radius,
        ball.radius * 2.0f, ball.radius * 2.0f};
    CrossEngine::ColorRGBA8 color;
    unsigned char colorVal = static_cast<unsigned char>(glm::clamp(
        glm::length(ball.velocity) * ball.mass * 12.0f, 0.0f, 255.0f));
    color.r = colorVal;
    color.g = colorVal;
    color.b = colorVal;
    color.a = colorVal;
    sprite_batch->Draw(dest_rect, uv_rect, ball.texture.texture,
                       ball.position.z, color);
  }

  sprite_batch->End();
  sprite_batch->RenderBatch();
}

VelocityBallRenderer::VelocityBallRenderer(int screen_width, int screen_height)
    : screen_width_(screen_width), screen_height_(screen_height) {
  // Empty
}

VelocityBallRenderer::~VelocityBallRenderer() {}

void VelocityBallRenderer::RenderBalls(CrossEngine::SpriteBatch* sprite_batch,
                                       const std::vector<Ball>& balls) {
  sprite_batch->Begin();

  // Render all the balls
  for (auto& ball : balls) {
    const CrossEngine::Rect uv_rect = {-1.0f, -1.0f, 2.0f, 2.0f};
    const CrossEngine::Rect dest_rect = {
        ball.position.x - ball.radius, ball.position.y - ball.radius,
        ball.radius * 2.0f, ball.radius * 2.0f};

    float mult = 100.0f;
    CrossEngine::ColorRGBA8 color;
    unsigned char colorVal = static_cast<unsigned char>(
        glm::clamp(ball.velocity.x * mult, 0.0f, 255.0f));
    color.r = 128;
    color.g = (ball.position.x / screen_width_) * 255.0f;
    color.b = (ball.position.y / screen_height_) * 255.0f;
    color.a = colorVal;
    sprite_batch->Draw(dest_rect, uv_rect, ball.texture.texture,
                       ball.position.z, color);
  }

  sprite_batch->End();
  sprite_batch->RenderBatch();
}

TrippyBallRenderer::TrippyBallRenderer(int screen_width, int screen_height)
    : screen_width_(screen_width), screen_height_(screen_height) {
  // Empty
}

TrippyBallRenderer::~TrippyBallRenderer() {}

void TrippyBallRenderer::RenderBalls(CrossEngine::SpriteBatch* sprite_batch,
                                     const std::vector<Ball>& balls) {
  sprite_batch->Begin();

  // Change these constants to get cool stuff
  float time_spend = 0.01f;
  float divisor = 4.0f;            // Increase to get more arms
  float spiral_intensity = 10.0f;  // Increase to make it spiral more

  time_ += time_spend;

  // Render all the balls
  for (auto& ball : balls) {
    const CrossEngine::Rect uv_rect = {-1.0f, -1.0f, 2.0f, 2.0f};
    const CrossEngine::Rect dest_rect = {
        ball.position.x - ball.radius, ball.position.y - ball.radius,
        ball.radius * 2.0f, ball.radius * 2.0f};
    // Get vector from center point
    glm::vec2 centerVec =
        ball.position - glm::vec3(screen_width_ / 2, screen_height_ / 2, 0.0f);
    float centerDist = glm::length(centerVec);

    // Get angle from the horizontal
    float angle = atan2(centerVec.x, centerVec.y) / (3.1415926 / divisor);

    // Move with time
    angle -= time_;

    // Add the spiral
    angle += (centerDist / screen_width_) * spiral_intensity;

    CrossEngine::ColorRGBA8 color;
    color.r = angle * 255.0f;
    color.g = angle * 255.0f * cos(time_);
    color.b = angle * 255.0f * sin(time_);
    color.a =
        glm::clamp(1.0f - (centerDist / (screen_width_ / 2.0f)), 0.0f, 1.0f) *
        255.0f;
    sprite_batch->Draw(dest_rect, uv_rect, ball.texture.texture,
                       ball.position.z, color);
  }

  sprite_batch->End();
  sprite_batch->RenderBatch();
}
