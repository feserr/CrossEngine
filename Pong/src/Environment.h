/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include <CrossEngine/InputManager.h>
#include <CrossEngine/SpriteBatch.h>
#include <CrossEngine/TileSheet.h>

class Environment {
  public:
    void Init(const glm::vec2& position, const glm::vec2& dimension,
        CrossEngine::ColorRGBA8 color);

    void Destroy();

    void Draw(CrossEngine::SpriteBatch& spriteBatch);

  private:
    glm::vec2 m_position;
    glm::vec2 m_dimension;
    CrossEngine::ColorRGBA8 m_color;
    CrossEngine::TileSheet m_texture;
};

#endif  // _ENVIRONMENT_H_
