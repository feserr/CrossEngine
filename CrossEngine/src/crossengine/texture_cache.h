/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_TEXTURECACHE_H_
#define CROSSENGINE_TEXTURECACHE_H_

#include <map>
#include <string>
#include "cross_texture.h"

namespace CrossEngine {
/**
 * @brief Class that caches the textures so that multiple sprites can use the
 * same textures.
 */
class TextureCache {
 public:
  /**
   * @brief Construct a new TextureCache object.
   */
  TextureCache();

  /**
   * @brief Destroy the TextureCache object.
   */
  ~TextureCache();

  /**
   * @brief Get the Texture object.
   *
   * @param[in] texture_path The path of the texture.
   * @return CrossTexture The texture.
   */
  CrossTexture GetTexture(std::string texture_path);

 private:
  std::map<std::string, CrossTexture> texture_map_;
};
}  // namespace CrossEngine

#endif  // CROSSENGINE_TEXTURECACHE_H_
