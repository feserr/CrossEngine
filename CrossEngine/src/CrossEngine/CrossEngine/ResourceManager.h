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

#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include <string>

#include "TextureCache.h"

namespace CrossEngine {
// This is a way for us to access all our resources, such as
// models or textures.
class ResourceManager {
 public:
    static CrossTexture GetTexture(std::string texturePath);

 private:
    static TextureCache m_textureCache;
};
}  // namespace CrossEngine

#endif  // _RESOURCEMANAGER_H_

