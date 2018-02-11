#include "BallRenderer.h"

#include <CrossEngine/CppUtils.h>

void BallRenderer::renderBalls(CrossEngine::SpriteBatch& spriteBatch,
    const std::vector<Ball>& balls,
    const glm::mat4& projectionMatrix) {
    spriteBatch.Begin();

    // Make sure the shader uses texture 0
    //glActiveTexture(GL_TEXTURE0);
    //GLint textureUniform = m_program->GetUniformLocation("mySampler");
    //glUniform1i(textureUniform, 0);

    // Grab the camera matrix
    //GLint pUniform = m_program->GetUniformLocation("P");
    //glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    // Render all the balls
    for (auto& ball : balls) {
        const glm::vec4 uvRect(-1.0f, -1.0f, 2.0f, 2.0f);
        const glm::vec4 destRect(ball.position.x - ball.radius,
            ball.position.y - ball.radius,
            ball.radius * 2.0f, ball.radius * 2.0f);
        spriteBatch.Draw(destRect, uvRect, ball.texture.texture, 0.0f,
            ball.color);
    }

    spriteBatch.End();
    spriteBatch.RenderBatch();

    //m_program->Unuse();
}
