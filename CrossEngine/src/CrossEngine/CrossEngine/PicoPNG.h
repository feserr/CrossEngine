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

#ifndef _PICOPNG_H_
#define _PICOPNG_H_

#include <vector>
#include <cstdio>

namespace CrossEngine {
    extern int DecodePNG(std::vector<unsigned char>& out_image,
        unsigned long& image_width, unsigned long& image_height,
        const unsigned char* in_png, size_t in_size,
        bool convert_to_rgba32 = true);
}  // namespace CrossEngine

#endif  // _PICOPNG_H_
