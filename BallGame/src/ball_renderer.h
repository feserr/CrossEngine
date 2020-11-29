/*
 * Copyright 2020 Elías Serrano. All rights reserved.
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
   */
  virtual void RenderBalls(CrossEngine::SpriteBatch* sprite_batch,
                           const std::vector<Ball>& balls);
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
   */
  virtual void RenderBalls(CrossEngine::SpriteBatch* sprite_batch,
                           const std::vector<Ball>& balls);
};

// Velocity ball renderer interface
class VelocityBallRenderer : public BallRenderer {
 public:
  /**
   * @brief Construct a new VelocityBallRenderer object.
   *
   * @param screen_width Width of the screen.
   * @param screen_height Height if the screen.
   */
  explicit VelocityBallRenderer(int screen_width, int screen_height);

  /**
   * @brief Destroy the VelocityBallRenderer object.
   */
  virtual ~VelocityBallRenderer();

  /**
   * @brief Render the balls using selected shader.
   *
   * @param[in] sprite_batch The SpriteBatch.
   * @param[in] balls The collection of balls.
   */
  virtual void RenderBalls(CrossEngine::SpriteBatch* sprite_batch,
                           const std::vector<Ball>& balls);

 private:
  int screen_width_, screen_height_;
};

// Trippy ball renderer interface
class TrippyBallRenderer : public BallRenderer {
 public:
  /**
   * @brief Construct a new TrippyBallRenderer object.
   *
   * @param screen_width Width of the screen.
   * @param screen_height Height if the screen.
   */
  explicit TrippyBallRenderer(int screen_width, int screen_height);

  /**
   * @brief Destroy the TrippyBallRenderer object.
   */
  virtual ~TrippyBallRenderer();

  /**
   * @brief Render the balls using selected shader.
   *
   * @param[in] sprite_batch The SpriteBatch.
   * @param[in] balls The collection of balls.
   */
  virtual void RenderBalls(CrossEngine::SpriteBatch* sprite_batch,
                           const std::vector<Ball>& balls);

 private:
  int screen_width_, screen_height_;
  float time_;
};

#endif  // BALLGAME_SRC_BALL_RENDERER_H_
