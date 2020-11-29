/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef BALLGAME_SRC_BALL_CONTROLLER_H_
#define BALLGAME_SRC_BALL_CONTROLLER_H_

#include <vector>

#include "ball.h"

enum class GravityDirection { NONE, LEFT, UP, RIGHT, DOWN };

class Grid;

class BallController {
 public:
  /**
   * @brief Update the balls.
   *
   * @param[in] balls The vector with all the balls.
   * @param[in] grid The grid.
   * @param[in] delta_time The delta time.
   * @param[in] max_x The maximun X axis position.
   * @param[in] max_y The maximun Y axis position.
   */
  void UpdateBalls(std::vector<Ball>* balls, Grid* grid, const float delta_time,
                   const int max_x, const int max_y);

  /**
   * @brief Called when the mouse select a ball.
   *
   * @param[in] balls The vector with all the balls.
   * @param[in] mouse_x The mouse X axis position.
   * @param[in] mouse_y The mouse Y axis position.
   */
  void OnMouseDown(std::vector<Ball>* balls, const float mouse_x,
                   const float mouse_y);

  /**
   * @brief Called when the mouse release the ball.
   *
   * @param[in] balls The vector with all the balls.
   */
  void OnMouseUp(std::vector<Ball>* balls);

  /**
   * @brief Called when the mouse moves.
   *
   * @param[in] balls The vector with all the balls.
   * @param[in] mouse_x The mouse X axis position.
   * @param[in] mouse_y The mouse Y axis position.
   */
  void OnMouseMove(std::vector<Ball>* balls, const float mouse_x,
                   const float mouse_y);

  /**
   * @brief Set the gravity direction object.
   *
   * @param[in] dir The direction of the gravity.
   */
  void SetGravityDirection(const GravityDirection dir) {
    gravity_direction_ = dir;
  }

 private:
  /**
   * @brief Updates collision.
   *
   * @param[in] grid The grid.
   */
  void UpdateCollision(Grid* grid);

  /**
   * @brief Checks collision between a ball and a vector of balls, starting at a
   * specific index.
   *
   * @param[in] ball The ball.
   * @param[in] balls_to_check The colection of balls.
   * @param[in] starting_index The starting index.
   */
  void CheckCollision(Ball* ball, std::vector<Ball*>* balls_to_check,
                      const int starting_index);

  /**
   * @brief Checks collision between two balls.
   *
   * @param[in] b1 The ball.
   * @param[in] b2 The other ball.
   */
  void CheckCollision(Ball* b1, Ball* b2);

  /**
   * @brief Check if the mouse is hovering over a ball.
   *
   * @param[in] b The ball.
   * @param[in] mouse_x The mouse X axis position.
   * @param[in] mouse_y The mouse Y axis position.
   * @return true If the mouse is hovering over a ball.
   * @return false Otherwise.
   */
  bool IsMouseOnBall(Ball* b, const float mouse_x, const float mouse_y);

  /**
   * @brief Get the gravity acceleration.
   *
   * @return glm::vec2 The acceleration.
   */
  glm::vec2 GetGravityAccel();

  // The ball we are currently grabbing on to.
  int grabbed_ball_ = -1;

  // Previous position of the grabbed ball.
  glm::vec3 previous_pos_ = glm::vec3(0.0f);

  // Offset of the cursor on the selected ball.
  glm::vec3 grab_offset_ = glm::vec3(0.0f);

  GravityDirection gravity_direction_ = GravityDirection::NONE;
};

#endif  // BALLGAME_SRC_BALL_CONTROLLER_H_
