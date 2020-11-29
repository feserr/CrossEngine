/*
 * Copyright 2020 Elías Serrano. All rights reserved.
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
  texture_.Init(texture, CrossEngine::i32Vector2({8, 1}));
}

void Environment::Destroy() {}

void Environment::Draw(CrossEngine::SpriteBatch* sprite_batch) {
  CrossEngine::Rect dest_rect = {position_.x - dimension_.x / 2.0f,
                                 position_.y - dimension_.y / 2.0f,
                                 dimension_.x, dimension_.y};

  CrossEngine::Rect uv_rect = texture_.GetUV(7);

  sprite_batch->Draw(dest_rect, uv_rect, texture_.texture.texture, 0.0f,
                     color_);
}
