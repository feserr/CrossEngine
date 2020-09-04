/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "crossengine/resource_manager.h"

#include <string>

namespace CrossEngine {
TextureCache ResourceManager::texture_cache_;

CrossTexture ResourceManager::GetTexture(std::string texture_path) {
  return texture_cache_.GetTexture(texture_path);
}
}  // namespace CrossEngine
