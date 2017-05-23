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

#include "CrossEngine/ImageLoader.h"
#include "CrossEngine/PicoPNG.h"
#include "CrossEngine/IOManager.h"
#include "CrossEngine/CrossErrors.h"

#include <bgfx/bgfx.h>
#include "../bgfx_utils.h"

#include <string>
#include <vector>

namespace CrossEngine {
    CrossTexture ImageLoader::LoadPNG(std::string &filePath, bool linear) {
        // Create a GLTexture and initialize all its fields to 0
        CrossTexture crossTexture = {};

        unsigned long width = 0, height = 0;

        // Decode the .png format into an array of pixels
        crossTexture.texture = loadTexture(filePath.data());
        /*if (crossTexture.texture.idx != BGFX_INVALID_HANDLE) {
            FatalError("Failed to load texture: " + filePath);
        }*/

        crossTexture.width = static_cast<int>(width);
        crossTexture.height = static_cast<int>(height);
        crossTexture.filePath = filePath;

        // Return a copy of the texture data
        return crossTexture;
    }
}  // namespace CrossEngine
