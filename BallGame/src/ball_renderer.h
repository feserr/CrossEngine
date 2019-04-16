/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef BALLGAME_SRC_BALL_RENDERER_H_
#define BALLGAME_SRC_BALL_RENDERER_H_

#include <crossengine/sprite_batch.h>
#include <memory>
#include <vector>
#include "ball.h"

// Ball renderer interface
class BallRenderer {
 public:
  /**
   * @brief Destroy the BallRenderer object.
   */
  virtual ~BallRenderer();

  /**
   * @brief Render the balls using selected shader.
   *
   * @param[in] sprite_batch The SpriteBatch.
   * @param[in] balls The collection of balls.
   * @param[in] projection_matrix The projection matrix.
   */
  virtual void RenderBalls(CrossEngine::SpriteBatch* sprite_batch,
                           const std::vector<Ball>& balls,
                           const glm::mat4& projection_matrix);
};

// Momentum ball renderer interface
class MomentumBallRenderer : public BallRenderer {
 public:
  /**
   * @brief Destroy the MomentumBallRenderer object.
   */
  virtual ~MomentumBallRenderer();

  /**
   * @brief Render the balls using selected shader.
   *
   * @param[in] sprite_batch The SpriteBatch.
   * @param[in] balls The collection of balls.
   * @param[in] projection_matrix The projection matrix.
   */
  virtual void RenderBalls(CrossEngine::SpriteBatch* sprite_batch,
                           const std::vector<Ball>& balls,
                           const glm::mat4& projection_matrix);
};

#endif  // BALLGAME_SRC_BALL_RENDERER_H_
