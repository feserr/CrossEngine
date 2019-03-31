/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github->com/feserr/crossengine#license
 */

#include "ball_controller.h"

#include "grid.h"

void BallController::UpdateBalls(std::vector<Ball>* balls, Grid* grid,
                                 const float delta_time, const int max_x,
                                 const int max_y) {
  const float FRICTION = 0.01f;
  // Update our grabbed balls velocity
  if (grabbed_ball_ != -1) {
    balls->at(grabbed_ball_).velocity =
        balls->at(grabbed_ball_).position - previous_pos_;
  }

  glm::vec2 gravity = GetGravityAccel();

  for (size_t i = 0; i < balls->size(); i++) {
    // get handle for less typing
    Ball& ball = balls->at(i);
    // Update motion if its not grabbed
    if (i != grabbed_ball_) {
      ball.position += ball.velocity * delta_time;
      // Apply friction
      glm::vec2 momentumVec = ball.velocity * ball.mass;
      if (momentumVec.x != 0 || momentumVec.y != 0) {
        if (FRICTION < glm::length(momentumVec)) {
          ball.velocity -=
              delta_time * FRICTION * glm::normalize(momentumVec) / ball.mass;
        } else {
          ball.velocity = glm::vec2(0.0f);
        }
      }
      // Apply gravity
      ball.velocity += gravity * delta_time;
    }
    // Check wall collision
    if (ball.position.x < ball.radius) {
      ball.position.x = ball.radius;
      if (ball.velocity.x < 0) ball.velocity.x *= -1;
    } else if (ball.position.x + ball.radius >= max_x) {
      ball.position.x = max_x - ball.radius - 1;
      if (ball.velocity.x > 0) ball.velocity.x *= -1;
    }
    if (ball.position.y < ball.radius) {
      ball.position.y = ball.radius;
      if (ball.velocity.y < 0) ball.velocity.y *= -1;
    } else if (ball.position.y + ball.radius >= max_y) {
      ball.position.y = max_y - ball.radius - 1;
      if (ball.velocity.y > 0) ball.velocity.y *= -1;
    }

    // Check to see if the ball moved
    Cell* newCell = grid->GetCell(ball.position);
    if (newCell != ball.ownerCell) {
      grid->RemoveBallFromCell(&balls->at(i));
      grid->AddBall(&balls->at(i), newCell);
    }
  }
  // Updates all collisions using the spatial partitioning
  UpdateCollision(grid);

  //// Update our grabbed ball
  if (grabbed_ball_ != -1) {
    // Update the velocity again, in case it got changed by collision
    balls->at(grabbed_ball_).velocity =
        balls->at(grabbed_ball_).position - previous_pos_;
    previous_pos_ = balls->at(grabbed_ball_).position;
  }
}

void BallController::OnMouseDown(std::vector<Ball>* balls, const float mouse_x,
                                 const float mouse_y) {
  for (size_t i = 0; i < balls->size(); i++) {
    // Check if the mouse is hovering over a ball
    if (IsMouseOnBall(&balls->at(i), mouse_x, mouse_y)) {
      grabbed_ball_ = i;  // BE AWARE, if you change the order of the balls in
                          // the vector, this becomes invalid!
      grab_offset_ = glm::vec2(mouse_x, mouse_y) - balls->at(i).position;
      previous_pos_ = balls->at(i).position;
      balls->at(i).velocity = glm::vec2(0.0f);
    }
  }
}

void BallController::OnMouseUp(std::vector<Ball>* balls) {
  if (grabbed_ball_ != -1) {
    // Throw the ball!
    balls->at(grabbed_ball_).velocity =
        balls->at(grabbed_ball_).position - previous_pos_;
    grabbed_ball_ = -1;
  }
}

void BallController::OnMouseMove(std::vector<Ball>* balls, const float mouse_x,
                                 const float mouse_y) {
  if (grabbed_ball_ != -1) {
    balls->at(grabbed_ball_).position =
        glm::vec2(mouse_x, mouse_y) - grab_offset_;
  }
}

void BallController::UpdateCollision(Grid* grid) {
  for (int i = 0; i < grid->cells_.size(); i++) {
    int x = i % grid->num_x_cells_;
    int y = i / grid->num_x_cells_;

    Cell& cell = grid->cells_.at(i);

    // Loop through all balls in a cell
    for (int j = 0; j < cell.balls.size(); j++) {
      Ball* ball = cell.balls[j];
      /// Update with the residing cell
      CheckCollision(ball, &cell.balls, j + 1);

      /// Update collision with neighbor cells
      if (x > 0) {
        // Left
        CheckCollision(ball, &grid->GetCell(x - 1, y)->balls, 0);
        if (y > 0) {
          /// Top left
          CheckCollision(ball, &grid->GetCell(x - 1, y - 1)->balls, 0);
        }
        if (y < grid->num_y_cells_ - 1) {
          // Bottom left
          CheckCollision(ball, &grid->GetCell(x - 1, y + 1)->balls, 0);
        }
      }
      // Up cell
      if (y > 0) {
        CheckCollision(ball, &grid->GetCell(x, y - 1)->balls, 0);
      }
    }
  }
}

void BallController::CheckCollision(Ball* ball,
                                    std::vector<Ball*>* balls_to_check,
                                    const int starting_index) {
  for (int i = starting_index; i < balls_to_check->size(); i++) {
    CheckCollision(ball, balls_to_check->at(i));
  }
}

void BallController::CheckCollision(Ball* b1, Ball* b2) {
  // We add radius since position is the top left corner
  glm::vec2 distVec = b2->position - b1->position;
  glm::vec2 distDir = glm::normalize(distVec);
  float dist = glm::length(distVec);
  float totalRadius = b1->radius + b2->radius;

  float collisionDepth = totalRadius - dist;
  // Check for collision
  if (collisionDepth > 0) {
    // Push away the less massive one
    if (b1->mass < b2->mass) {
      b1->position -= distDir * collisionDepth;
    } else {
      b2->position += distDir * collisionDepth;
    }

    // Calculate deflection. http://stackoverflow.com/a/345863
    // Fixed thanks to youtube user Sketchy502
    float aci = glm::dot(b1->velocity, distDir);
    float bci = glm::dot(b2->velocity, distDir);

    float acf = (aci * (b1->mass - b2->mass) + 2 * b2->mass * bci) /
                (b1->mass + b2->mass);
    float bcf = (bci * (b2->mass - b1->mass) + 2 * b1->mass * aci) /
                (b1->mass + b2->mass);

    b1->velocity += (acf - aci) * distDir;
    b2->velocity += (bcf - bci) * distDir;
  }
}

bool BallController::IsMouseOnBall(Ball* b, const float mouse_x,
                                   const float mouse_y) {
  return (mouse_x >= b->position.x - b->radius &&
          mouse_x < b->position.x + b->radius &&
          mouse_y >= b->position.y - b->radius &&
          mouse_y < b->position.y + b->radius);
}

glm::vec2 BallController::GetGravityAccel() {
  const float GRAVITY_FORCE = 0.02f;
  glm::vec2 gravity;

  switch (gravity_direction_) {
    case GravityDirection::DOWN:
      gravity = glm::vec2(0.0f, -GRAVITY_FORCE);
      break;
    case GravityDirection::LEFT:
      gravity = glm::vec2(-GRAVITY_FORCE, 0.0f);
      break;
    case GravityDirection::RIGHT:
      gravity = glm::vec2(GRAVITY_FORCE, 0.0f);
      break;
    case GravityDirection::UP:
      gravity = glm::vec2(0.0f, GRAVITY_FORCE);
      break;
    default:
      gravity = glm::vec2(0.0f);
      break;
  }
  return gravity;
}
