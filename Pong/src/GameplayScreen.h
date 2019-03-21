/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef GameplayScreen_h
#define GameplayScreen_h

#include "Player.h"
#include "Ball.h"
#include "Environment.h"

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

    CrossEngine::SpriteBatch m_spriteBatch;
    CrossEngine::Camera2D m_camera;
    CrossEngine::CrossTexture m_texture;
    CrossEngine::Window* m_window;

    Player m_playerOne;
    Player m_playerTwo;
    Ball m_ball;
    std::vector<Environment> m_enviroment;

    int m_iScorePlayerOne = 0, m_iScorePlayerTwo = 0;

    glm::vec2 m_windowSize;
};

#endif /* GameplayScreen_h */
