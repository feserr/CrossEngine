/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "crossengine/image_loader.h"

#include <string>
#include <vector>

#include "crossengine/bgfx_utils.h"
#include "crossengine/error_manager.h"
#include "crossengine/io_manager.h"

namespace CrossEngine {
CrossTexture ImageLoader::LoadPNG(const std::string &file_path) {
  // Create a GLTexture and initialize all its fields to 0
  CrossTexture crossTexture = {};

  bgfx::TextureInfo info = bgfx::TextureInfo();

  // Decode the .png format into an array of pixels
  crossTexture.texture =
      loadTexture(file_path.data(),
                  BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT, 0, &info);
  if (!bgfx::isValid(crossTexture.texture)) {
    FatalError("Failed to load texture: " + file_path);
  }

  crossTexture.width = info.width;
  crossTexture.height = info.height;
  crossTexture.file_path = file_path;

  // Return a copy of the texture data
  return crossTexture;
}
}  // namespace CrossEngine
