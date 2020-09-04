/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_RESOURCEMANAGER_H_
#define CROSSENGINE_RESOURCEMANAGER_H_

#include <string>

#include "texture_cache.h"

namespace CrossEngine {
/**
 * @brief Class to access the resources.
 */
class ResourceManager {
 public:
  /**
   * @brief Gets a texture.
   *
   * @param[in] texture_path The path to the texture.
   * @return CrossTexture The texture.
   */
  static CrossTexture GetTexture(std::string texture_path);

 private:
  static TextureCache texture_cache_;
};
}  // namespace CrossEngine

#endif  // CROSSENGINE_RESOURCEMANAGER_H_
