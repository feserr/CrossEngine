/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "ball.h"

#include <crossengine/resource_manager.h>
#include <SDL/SDL.h>
#include <random>

void Ball::Init(const glm::vec2& position, const glm::vec2& velocity,
                const float radious, const float mass) {
  position_ = position;
  velocity_ =velocity;
  color_ = CrossEngine::ColorRGBA8(255, 255, 255, 255);
  radious_ = radious;
  mass_ = mass;
  texture_.Init(CrossEngine::ResourceManager::GetTexture("images/Pong.png"),
                glm::ivec2(8, 1));
}

void Ball::Destroy() {}

int Ball::Update(const float delta_time, const glm::vec2& window_size) {
  const float FRICTION = 0.01f;

  glm::vec2 gravity(0.0f);

  position_ += velocity_ * delta_time;
  // Apply friction
  glm::vec2 momentumVec = velocity_ * mass_;
  if (momentumVec.x != 0 || momentumVec.y != 0) {
    if (FRICTION < glm::length(momentumVec)) {
      velocity_ -= delta_time * FRICTION * glm::normalize(momentumVec) / mass_;
    } else {
      velocity_ = glm::vec2(0.0f);
    }
  }

  // Apply gravity
  velocity_ += gravity * delta_time;

  // Check wall collision
  if (position_.x < radious_) {
    position_.x = radious_;
    if (velocity_.x < 0) {
      // velocity_.x *= -1;
      RestartPosition(window_size);
      return 1;
    }
  } else if (position_.x + radious_ >= window_size.x) {
    position_.x = window_size.x - radious_ - 1;
    if (velocity_.x > 0) {
      // velocity_.x *= -1;
      RestartPosition(window_size);
      return 2;
    }
  }

  if (position_.y < radious_) {
    position_.y = radious_;
    if (velocity_.y < 0) {
      velocity_.y *= -1;
    }
  } else if (position_.y + radious_ >= window_size.y) {
    position_.y = window_size.y - radious_ - 1;
    if (velocity_.y > 0) {
      velocity_.y *= -1;
    }
  }

  return 0;
}

void Ball::Draw(CrossEngine::SpriteBatch* sprite_batch) {
  // Get the uv coordinates from the tile index
  glm::vec4 uvRect = texture_.GetUVs(6);
  const glm::vec4 destRect(position_.x - radious_, position_.y - radious_,
                           radious_ * 2.0f, radious_ * 2.0f);
  sprite_batch->Draw(destRect, uvRect, texture_.texture.texture, 0.0f, color_);
}

void Ball::RestartPosition(const glm::vec2& window_size) {
  std::mt19937 randomEngine((unsigned int)time(nullptr));
  std::uniform_real_distribution<float> r1(-1.0f, 1.0f);
  position_ = glm::vec2(window_size.x / 2, window_size.y / 2);
  velocity_ =
      glm::vec2(6 * std::copysign(1.0f, r1(randomEngine)), r1(randomEngine));
}
