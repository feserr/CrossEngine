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

#include "CrossEngine/TextureCache.h"
#include "CrossEngine/ImageLoader.h"

#include <string>
#include <iostream>

namespace CrossEngine {
    TextureCache::TextureCache() {
    }

    TextureCache::~TextureCache() {
    }

    CrossTexture TextureCache::GetTexture(std::string texturePath) {
        // Lookup the texture and see if its in the map
        auto mit = m_textureMap.find(texturePath);

        // Check if its not in the map
        if (mit == m_textureMap.end()) {
            // Load the texture
            CrossTexture newTexture = ImageLoader::LoadPNG(texturePath);

            // Insert it into the map
            m_textureMap.insert(make_pair(texturePath, newTexture));

            return newTexture;
        }
        return mit->second;
    }
}  // namespace CrossEngine
