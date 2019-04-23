/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_TILESHEET_H_
#define CROSSENGINE_TILESHEET_H_

#include <glm/glm.hpp>
#include "cross_texture.h"

namespace CrossEngine {
/**
 * @brief Class for tile sheets.
 */
class TileSheet {
 public:
  /**
   * @brief Initialize the object.
   *
   * @param[in] in_texture The texture for the tile sheet.
   * @param[in] tile_dimensions The dimension of the tile.
   */
  void Init(const CrossTexture& in_texture, const glm::ivec2& tile_dimensions) {
    this->texture = in_texture;
    this->dimensions = tile_dimensions;
  }

  /**
   * @brief Get the texture UV of the tile.
   *
   * @param index The index of the tile.
   * @return glm::vec4 The texture UV of the tile.
   */
  glm::vec4 GetUVs(int index) {
    int x_tile = index % dimensions.x;
    int y_tile = index / dimensions.x;
    float w_tile = (1.0f / dimensions.x) * 2;
    float h_tile = (1.0f / dimensions.y) * 2;

    glm::vec4 uvs;
    uvs.x = -1 + ((x_tile)*w_tile);
    uvs.y = -1 + ((y_tile)*h_tile);
    uvs.z = w_tile;
    uvs.w = h_tile;

    return uvs;
  }

  CrossTexture texture;
  glm::ivec2 dimensions;
};
}  // namespace CrossEngine

#endif  // CROSSENGINE_TILESHEET_H_
