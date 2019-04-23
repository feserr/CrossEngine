/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef PONG_SRC_BALL_H_
#define PONG_SRC_BALL_H_

#include <crossengine/input_manager.h>
#include <crossengine/sprite_batch.h>
#include <crossengine/tile_sheet.h>
#include <crossengine/vertex.h>

class Ball {
 public:
  /**
   * @brief Initialize the ball.
   *
   * @param[in] position The starting position.
   * @param[in] velocity The starting velocity.
   * @param[in] radious The radious.
   * @param[in] mass The mass.
   */
  void Init(const glm::vec2& position, const glm::vec2& velocity,
            const float radious, const float mass);

  /**
   * @brief Destroy the ball.
   */
  void Destroy();

  /**
   * @brief Main loop of the ball.
   *
   * @param[in] delta_time The delta time.
   * @param[in] window_size The size of the window.
   * @return int
   */
  int Update(const float delta_time, const glm::vec2& window_size);

  /**
   * @brief Render the ball in the sprite batch.
   *
   * @param[in] sprite_batch The main sprite batch.
   */
  void Draw(CrossEngine::SpriteBatch* sprite_batch);

  /**
   * @brief Restart the position of the ball.
   *
   * @param[in] window_size The size of the window.
   */
  void RestartPosition(const glm::vec2& window_size);

  /**
   * @brief Get the position object.
   *
   * @return const glm::vec2& The position of the ball.
   */
  const glm::vec2& GetPosition() const { return position_; }

  /**
   * @brief Get the radius object.
   *
   * @return const float The radious of the ball.
   */
  const float GetRadious() const { return radious_; }

  /**
   * @brief Set the velocity of the ball.
   *
   * @param[in] velocity The new velocity.
   */
  void SetVelocity(const glm::vec2& velocity) { velocity_ = velocity; }

 private:
  glm::vec2 position_;
  glm::vec2 velocity_;
  CrossEngine::ColorRGBA8 color_;
  CrossEngine::TileSheet texture_;
  float radious_;
  float mass_;
};

#endif  // PONG_SRC_BALL_H_
