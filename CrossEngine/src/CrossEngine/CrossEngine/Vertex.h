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

#ifndef _VERTEX_H_
#define _VERTEX_H_

namespace CrossEngine {
struct Position {
    float x;
    float y;
};

struct ColorRGBA8 {
    ColorRGBA8() : r(0), g(0), b(0), a(0) { }
    ColorRGBA8(unsigned char R, unsigned char G, unsigned char B, 
        unsigned char A) :
        r(R), g(G), b(B), a(A) { }
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

struct UV {
    float u;
    float v;
};

// The vertex definition
struct Vertex {
    // This is the position struct. When you store a struct or class
    // inside of another struct or class, it is called composition. This is
    // layed out exactly the same in memory as if we had a float position[2],
    // but doing it this way makes more sense.
    Position position;

    // 4 bytes for r g b a color.
    ColorRGBA8 color;

    // UV texture coordinates.
    UV uv;

    void SetPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }

    void SetColor(unsigned char r, unsigned char g, unsigned char b, 
        unsigned char a) {
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
    }

    void SetUV(float u, float v) {
        uv.u = u;
        uv.v = v;
    }
};
}  // namespace CrossEngine

#endif  // _VERTEX_H_
