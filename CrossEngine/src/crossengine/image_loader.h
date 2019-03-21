/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_IMAGELOADER_H_
#define CROSSENGINE_IMAGELOADER_H_

#include <string>
#include "cross_texture.h"

namespace CrossEngine {
/// Loads images into Cross Engine textures.
class ImageLoader {
 public:
  /**
   * @brief Loads a png.
   *
   * @param[in] file_path  The file path
   * @param[in] linear If linear==true apply linear filter to the texture,
   *                   if linear==false apply nearest filter
   * @return An Cross Engine texture of the texture file.
   */
  static CrossTexture LoadPNG(const std::string& file_path,
                              bool linear = false);
};
}  // namespace CrossEngine

#endif  // CROSSENGINE_IMAGELOADER_H_
