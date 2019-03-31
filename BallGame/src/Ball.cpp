/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "ball.h"

Ball::Ball(float rad, float m, const glm::vec2& pos, const glm::vec2& vel,
           CrossEngine::CrossTexture tex, const CrossEngine::ColorRGBA8& col) {
  radius = rad;
  mass = m;
  position = pos;
  velocity = vel;
  texture = tex;
  color = col;
}
