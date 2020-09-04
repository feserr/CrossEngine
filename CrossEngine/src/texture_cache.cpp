/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "crossengine/texture_cache.h"

#include <iostream>
#include <string>
#include "crossengine/image_loader.h"

namespace CrossEngine {
TextureCache::TextureCache() {}

TextureCache::~TextureCache() { texture_map_.clear(); }

CrossTexture TextureCache::GetTexture(std::string texture_path) {
  // Lookup the texture and see if its in the map
  auto mit = texture_map_.find(texture_path);

  // Check if its not in the map
  if (mit == texture_map_.end()) {
    // Load the texture
    CrossTexture newTexture = ImageLoader::LoadPNG(texture_path);

    // Insert it into the map
    texture_map_.insert(make_pair(texture_path, newTexture));

    return newTexture;
  }
  return mit->second;
}
}  // namespace CrossEngine
