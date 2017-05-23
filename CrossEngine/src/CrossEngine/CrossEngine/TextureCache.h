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

#ifndef _TEXTURECACHE_H_
#define _TEXTURECACHE_H_

#include "CrossTexture.h"

#include <string>
#include <map>

namespace CrossEngine {
// This caches the textures so that multiple sprites can use the same textures
class TextureCache {
 public:
    TextureCache();
    ~TextureCache();

    CrossTexture GetTexture(std::string texturePath);

 private:
    std::map<std::string, CrossTexture> m_textureMap;
};
}  // namespace CrossEngine

#endif  // _TEXTURECACHE_H_
