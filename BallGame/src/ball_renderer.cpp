/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "ball_renderer.h"

#include <crossengine/cpp_utils.h>

BallRenderer::~BallRenderer() {}

void BallRenderer::RenderBalls(CrossEngine::SpriteBatch* sprite_batch,
                               const std::vector<Ball>& balls,
                               const glm::mat4& projection_matrix) {
  sprite_batch->Begin();

  // Make sure the shader uses texture 0
  // glActiveTexture(GL_TEXTURE0);
  // GLint textureUniform = m_program->GetUniformLocation("mySampler");
  // glUniform1i(textureUniform, 0);

  // Grab the camera matrix
  // GLint pUniform = m_program->GetUniformLocation("P");
  // glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projection_matrix[0][0]);

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

  // m_program->Unuse();
}
