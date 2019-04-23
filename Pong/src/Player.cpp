/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "Player.h"

#include <SDL/SDL.h>
#include <crossengine/input_manager.h>
#include <crossengine/common.h>
#include <crossengine/resource_manager.h>
#include <entry/entry.h>
#include <entry/input.h>
#include <iostream>

const float MAX_VELOCITY = 5.0f;

void Player::Init(const glm::vec2& position, const glm::vec2& draw_dimensions,
                  const glm::vec2& collision_dimensions,
                  const CrossEngine::ColorRGBA8 color,
                  const PlayerType player_type) {
  position_ = position;
  color_ = color;
  draw_dimensions_ = draw_dimensions;
  collision_dimensions_ = collision_dimensions;
  velocity_ = glm::vec2(0.0f);
  texture_.Init(CrossEngine::ResourceManager::GetTexture("images/Pong.png"),
                glm::ivec2(8, 1));
  player_type_ = player_type;
}

void Player::Destroy() {}

void Player::Draw(CrossEngine::SpriteBatch* sprite_batch) {
  glm::vec4 destRect;
  destRect.x = position_.x - draw_dimensions_.x / 2.0f;
  destRect.y = position_.y - draw_dimensions_.y / 2.0f;
  destRect.z = draw_dimensions_.x;
  destRect.w = draw_dimensions_.y;

  int tileIndex;
  int numTiles;

  glm::vec2 velocity;
  velocity.x = velocity_.x;
  velocity.y = velocity_.y;

  if (std::abs(velocity.y) > 1.0f) {
    // Moving
    numTiles = 1;
    tileIndex = 0;
    move_state_ = PlayerMoveState::MOVING;
  } else {
    // Standing still
    numTiles = 1;
    tileIndex = 0;
    move_state_ = PlayerMoveState::STANDING;
  }

  // Get the uv coordinates from the tile index
  glm::vec4 uvRect = texture_.GetUVs(tileIndex);
  glm::vec4 uvRectBottom = texture_.GetUVs(tileIndex + 1);
  glm::vec4 uvRectTop = texture_.GetUVs(tileIndex + 2);

  // Draw the sprite
  // m_sprite.Draw(&texture_);
  // Draw the sprite
  sprite_batch->Draw(destRect, uvRect, texture_.texture.texture, 0.0f, color_);
  destRect.y = position_.y + draw_dimensions_.y / 2;
  sprite_batch->Draw(destRect, uvRectTop, texture_.texture.texture, 0.0f,
                     color_);
  destRect.y = position_.y - draw_dimensions_.y * 1.5;
  sprite_batch->Draw(destRect, uvRectBottom, texture_.texture.texture, 0.0f,
                     color_);
}

void Player::Update(const float delta_time, const glm::vec2& window_size,
                    Ball* ball) {
  // Check inputs and update the player stats
  if (CrossEngine::InputManager::instance().IsKeyDown(entry::Key::KeyW) &&
      player_type_ == PlayerType::PLAYERONE) {
    velocity_.y = -MAX_VELOCITY;
  } else if (CrossEngine::InputManager::instance().IsKeyDown(
                 entry::Key::KeyS) &&
             player_type_ == PlayerType::PLAYERONE) {
    velocity_.y = MAX_VELOCITY;
  } else if (CrossEngine::InputManager::instance().IsKeyDown(entry::Key::Up) &&
             player_type_ == PlayerType::PLAYERTWO) {
    velocity_.y = -MAX_VELOCITY;
  } else if (CrossEngine::InputManager::instance().IsKeyDown(
                 entry::Key::Down) &&
             player_type_ == PlayerType::PLAYERTWO) {
    velocity_.y = MAX_VELOCITY;
  }

  // Check if the player goes out of the window
  if (velocity_.y < 0 && position_.y - draw_dimensions_.y <= 0) {
    velocity_.y = 0;
  } else if (velocity_.y > 0 &&
             position_.y + draw_dimensions_.y >= window_size.y) {
    velocity_.y = 0;
  }

  // Set position
  position_ += velocity_ * delta_time;

  // Handle the velocity
  if (std::abs(velocity_.y) > 0.01f) {
    velocity_.y =
        (std::abs(velocity_.y) - MAX_VELOCITY / 2) * (velocity_.y > 0 ? 1 : -1);
  } else {
    velocity_.y = 0.0f;
  }

  // Ball collision
  glm::vec2 ballPosition = ball->GetPosition();
  glm::vec2 newVelocity;
  // Check if they are at the same y position
  if (position_.y - collision_dimensions_.y / 2 <=
      ballPosition.y + ball->GetRadious() &&
      position_.y + collision_dimensions_.y / 2 >=
      ballPosition.y - ball->GetRadious()) {
    float yCollision = (ballPosition.y - position_.y) / 4;
    if (player_type_ == PlayerType::PLAYERONE &&
        position_.x + collision_dimensions_.x >=
        ballPosition.x + ball->GetRadious()) {
      newVelocity = glm::vec2(6.0f, yCollision);
      ball->SetVelocity(newVelocity);
    } else if (player_type_ == PlayerType::PLAYERTWO &&
               position_.x - collision_dimensions_.x <=
                   ballPosition.x - ball->GetRadious()) {
      newVelocity = glm::vec2(-6.0f, yCollision);
      ball->SetVelocity(newVelocity);
    }
  }
}
