/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef PONG_SRC_ENVIRONMENT_H_
#define PONG_SRC_ENVIRONMENT_H_

#include <crossengine/input_manager.h>
#include <crossengine/sprite_batch.h>
#include <crossengine/tile_sheet.h>

class Environment {
 public:
  /**
   * @brief Initialize the enviroment.
   *
   * @param[in] position The position.
   * @param[in] dimension The dimension.
   * @param[in] color The color.
   */
  void Init(const glm::vec2& position, const glm::vec2& dimension,
            const CrossEngine::ColorRGBA8 color);

  /**
   * @brief Destroy the enviroment object.
   *
   */
  void Destroy();

  /**
   * @brief Render the enviroment in the sprite batch.
   *
   * @param[in] sprite_batch The main sprite batch.
   */
  void Draw(CrossEngine::SpriteBatch* sprite_batch);

 private:
  glm::vec2 position_;
  glm::vec2 dimension_;
  CrossEngine::ColorRGBA8 color_;
  CrossEngine::TileSheet texture_;
};

#endif  // PONG_SRC_ENVIRONMENT_H_
