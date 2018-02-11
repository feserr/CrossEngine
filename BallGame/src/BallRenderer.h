#pragma once

#include <CrossEngine/SpriteBatch.h>
#include <vector>
#include <memory>
#include "Ball.h"

// Ball renderer interface
class BallRenderer {
public:
    virtual void renderBalls(CrossEngine::SpriteBatch& spriteBatch, const std::vector<Ball>& balls,
                             const glm::mat4& projectionMatrix);
protected:
    //std::unique_ptr<CrossEngine::GLSLProgram> m_program = nullptr;
};
