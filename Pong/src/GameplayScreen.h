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

#ifndef GameplayScreen_h
#define GameplayScreen_h

#include "Player.h"

#include <CrossEngine/IGameScreen.h>
#include <CrossEngine/SpriteBatch.h>
#include <CrossEngine/Camera2D.h>
#include <CrossEngine/CrossTexture.h>
#include <CrossEngine/Window.h>
#include <vector>

static const uint16_t textureside   = 512;
static const uint32_t texture2dSize = 256;

// Our custom gameplay screen that inherits from the IGameScreen
class GameplayScreen : public CrossEngine::IGameScreen {
public:
    GameplayScreen(CrossEngine::Window* window);
    ~GameplayScreen();

    virtual int GetNextScreenIndex() const override;

    virtual int GetPreviousScreenIndex() const override;

    virtual void Build() override;

    virtual void Destroy() override;

    virtual void OnEntry() override;

    virtual void OnExit() override;

    virtual void Update() override;

    virtual void Draw() override;

private:
    void initUI();
    void checkInput();

    bool onExitClicked();

    bgfx::ProgramHandle m_program;
    bgfx::UniformHandle s_texColor;
    bgfx::TextureHandle m_textures[9];
    bgfx::IndexBufferHandle m_ibh;
    bgfx::VertexBufferHandle m_vbh;

    CrossEngine::SpriteBatch m_spriteBatch;
    CrossEngine::Camera2D m_camera;
    CrossEngine::CrossTexture m_texture;
    CrossEngine::Window* m_window;

    Player m_playerOne;
    Player m_playerTwo;
    //Ball m_ball;
    //std::vector<Environment> m_enviroment;

    int m_iScorePlayerOne = 0, m_iScorePlayerTwo = 0;

    glm::vec2 m_windowSize;
};

#endif /* GameplayScreen_h */
