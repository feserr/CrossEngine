/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "environment.h"

#include <crossengine/resource_manager.h>

void Environment::Init(const glm::vec2& position, const glm::vec2& dimension,
                       const CrossEngine::ColorRGBA8 color) {
  position_ = position;
  dimension_ = dimension;
  color_ = color;
  CrossEngine::CrossTexture texture =
      CrossEngine::ResourceManager::GetTexture("images/Pong.png");
  texture_.Init(texture, glm::ivec2(8, 1));
}

void Environment::Destroy() {}

void Environment::Draw(CrossEngine::SpriteBatch* sprite_batch) {
  glm::vec4 destRect;
  destRect.x = position_.x - dimension_.x / 2.0f;
  destRect.y = position_.y - dimension_.y / 2.0f;
  destRect.z = dimension_.x;
  destRect.w = dimension_.y;

  glm::vec4 uvRect = texture_.GetUVs(7);

  sprite_batch->Draw(destRect, uvRect, texture_.texture.texture, 0.0f, color_);
}
