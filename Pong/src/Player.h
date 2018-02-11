/*
    Copyright 2017-2018 Elías Serrano. All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY COPYRIGHT HOLDER ``AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
    PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER OR
    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
    OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Ball.h"

#include <CrossEngine/InputManager.h>
#include <CrossEngine/Sprite.h>
#include <CrossEngine/Vertex.h>
#include <CrossEngine/TileSheet.h>
#include <CrossEngine/SpriteBatch.h>

enum class PlayerMoveState {STANDING, MOVING};
enum class PlayerType { PLAYERONE, PLAYERTWO, BOT};

class Player {
public:
    void Init(const glm::vec2& position, const glm::vec2& drawDims,
        glm::vec2& collisionDims, CrossEngine::ColorRGBA8 color,
        PlayerType playerType);

    void Destroy();

    void Draw(CrossEngine::SpriteBatch& spriteBatch);
    
    void Update(float deltaTime, CrossEngine::InputManager& inputManager,
        const glm::vec2 &windowSize, Ball &ball);

    glm::vec2 GetPosition() const {
        glm::vec2 rv;
        rv.x = m_position.x;
        rv.y = m_position.y;
        return rv;
    }

    const glm::vec2& GetDrawDims() const { return m_drawDims; }
    const glm::vec2& GetCollisionDims() const { return m_collisionDims; }
    const CrossEngine::ColorRGBA8& GetColor() const { return m_color; }

private:
    glm::vec2 m_drawDims;
    glm::vec2 m_collisionDims;
    CrossEngine::ColorRGBA8 m_color;
    CrossEngine::TileSheet m_texture;
    PlayerMoveState m_moveState = PlayerMoveState::STANDING;
    glm::vec2 m_position;
    glm::vec2 m_velocity;
    PlayerType m_playerType;
};



#endif  // _PLAYER_H_
