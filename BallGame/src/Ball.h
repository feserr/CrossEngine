/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef BALLGAME_SRC_BALL_H_
#define BALLGAME_SRC_BALL_H_

#include <crossengine/cross_texture.h>
#include <crossengine/vertex.h>
#include <glm/glm.hpp>

struct Cell;

// POD
struct Ball {
  /**
   * @brief Construct a new Ball object.
   *
   * @param rad The radius.
   * @param m The mass.
   * @param pos The position.
   * @param vel The velocity.
   * @param texture The texture.
   * @param color The color.
   */
  Ball(float rad, float m, const glm::vec2& pos, const glm::vec2& vel,
       CrossEngine::CrossTexture tex, const CrossEngine::ColorRGBA8& col);

  float radius;
  float mass;
  glm::vec2 velocity;
  glm::vec2 position;
  CrossEngine::CrossTexture texture;
  CrossEngine::ColorRGBA8 color;
  Cell* ownerCell;
  int cellVectorIndex;
};

#endif  // BALLGAME_SRC_BALL_H_
