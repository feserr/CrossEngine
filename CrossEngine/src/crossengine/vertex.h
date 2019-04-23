/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_VERTEX_H_
#define CROSSENGINE_VERTEX_H_

namespace CrossEngine {
/**
 * @brief Position definition.
 */
struct Position {
  float x;
  float y;
};

/**
 * @brief Color definition.
 *
 */
struct ColorRGBA8 {
  /**
   * @brief Construct a new ColorRGBA8 object.
   */
  ColorRGBA8() : r(0), g(0), b(0), a(0) {}

  /**
   * @brief Construct a new ColorRGBA8 object.
   *
   * @param[in] R The red value.
   * @param[in] G The green value.
   * @param[in] B The blue value.
   * @param[in] A The alpha value.
   */
  ColorRGBA8(unsigned char R, unsigned char G, unsigned char B, unsigned char A)
      : r(R), g(G), b(B), a(A) {}

  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
};

/**
 * @brief Texture UV definition.
 */
struct UV {
  float u;
  float v;
};

/**
 * @brief Vertex definition.
 */
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

  /**
   * @brief Set the position of the object.
   *
   * @param[in] x The X axis position.
   * @param[in] y The Y axis position.
   */
  void SetPosition(float x, float y) {
    position.x = x;
    position.y = y;
  }

  /**
   * @brief Set the color of the object.
   *
   * @param[in] r The red value.
   * @param[in] g The green value.
   * @param[in] b The blue value.
   * @param[in] a The alpha value.
   */
  void SetColor(unsigned char r, unsigned char g, unsigned char b,
                unsigned char a) {
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
  }

  /**
   * @brief Set the texture UV of the object.
   *
   * @param[in] u The U axis of the texture.
   * @param[in] v The V axis of the texture.
   */
  void SetUV(float u, float v) {
    uv.u = u;
    uv.v = v;
  }
};
}  // namespace CrossEngine

#endif  // CROSSENGINE_VERTEX_H_
