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

#ifndef _TILESHEET_H_
#define _TILESHEET_H_

#include "CrossTexture.h"

#include <glm/glm.hpp>

namespace CrossEngine {
class TileSheet {
 public:
    void Init(const GLTexture& texture, const glm::ivec2& tileDims) {
        this->texture = texture;
        this->dims = tileDims;
    }

    glm::vec4 GetUVs(int index) {
        int xTile = index % dims.x;
        int yTile = index / dims.x;

        glm::vec4 uvs;
        uvs.x = xTile / static_cast<float>(dims.x);
        uvs.y = yTile / static_cast<float>(dims.y);
        uvs.z = 1.0f / dims.x;
        uvs.w = 1.0f / dims.y;

        return uvs;
    }

    GLTexture texture;
    glm::ivec2 dims;
};
}  // namespace CrossEngine

#endif  // _TILESHEET_H_
