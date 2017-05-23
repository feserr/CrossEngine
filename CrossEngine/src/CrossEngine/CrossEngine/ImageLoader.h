/*
    Copyright [2016] [Elías Serrano]

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _IMAGELOADER_H_
#define _IMAGELOADER_H_

#include "CrossTexture.h"

#include <string>

namespace CrossEngine {
/// Loads images into GLTextures
class ImageLoader {
 public:
    /**
     * \brief      Loads a png.
     *
     * \param[in]  filePath  The file path
     * \param[in]  linear  If linear==true apply linear filter to the texture,
                           if linear==false apply nearest filter
     *
     * \return     An GLTexture of the texture file.
     */
    static CrossTexture LoadPNG(std::string &filePath, bool linear = false);
};
}  // namespace CrossEngine

#endif  // _IMAGELOADER_H_
