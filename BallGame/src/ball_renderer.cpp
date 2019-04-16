/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "ball_renderer.h"

#include <crossengine/cpp_utils.h>
#include <glm/glm.hpp>

BallRenderer::~BallRenderer() {}

void BallRenderer::RenderBalls(CrossEngine::SpriteBatch* sprite_batch,
                               const std::vector<Ball>& balls,
                               const glm::mat4& projection_matrix) {
  sprite_batch->Begin();

  // Render all the balls
  for (auto& ball : balls) {
    const glm::vec4 uvRect(-1.0f, -1.0f, 2.0f, 2.0f);
    const glm::vec4 destRect(ball.position.x - ball.radius,
                             ball.position.y - ball.radius, ball.radius * 2.0f,
                             ball.radius * 2.0f);
    sprite_batch->Draw(destRect, uvRect, ball.texture.texture, 0.0f,
                       ball.color);
  }

  sprite_batch->End();
  sprite_batch->RenderBatch();
}

MomentumBallRenderer::~MomentumBallRenderer() {}

void MomentumBallRenderer::RenderBalls(CrossEngine::SpriteBatch* sprite_batch,
                                       const std::vector<Ball>& balls,
                                       const glm::mat4& projection_matrix) {
  sprite_batch->Begin();

  // Render all the balls
  for (auto& ball : balls) {
    const glm::vec4 uvRect(-1.0f, -1.0f, 2.0f, 2.0f);
    const glm::vec4 destRect(ball.position.x - ball.radius,
                             ball.position.y - ball.radius, ball.radius * 2.0f,
                             ball.radius * 2.0f);
    CrossEngine::ColorRGBA8 color;
    unsigned char colorVal = static_cast<unsigned char>(glm::clamp(
        glm::length(ball.velocity) * ball.mass * 12.0f, 0.0f, 255.0f));
    color.r = colorVal;
    color.g = colorVal;
    color.b = colorVal;
    color.a = colorVal;
    sprite_batch->Draw(destRect, uvRect, ball.texture.texture, 0.0f,
                       ball.color);
  }

  sprite_batch->End();
  sprite_batch->RenderBatch();
}
