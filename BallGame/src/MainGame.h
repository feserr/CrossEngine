#pragma once

#include <CrossEngine/IGameScreen.h>
#include <CrossEngine/Camera2D.h>
#include <CrossEngine/SpriteBatch.h>
#include <CrossEngine/InputManager.h>
#include <CrossEngine/Window.h>
#include <CrossEngine/Timing.h>
#include <memory>

#include "BallController.h"
#include "BallRenderer.h"
#include "Grid.h"

// TODO:
// Visualize momentum with color
// Visualize velocity with color
// Visualize position with color

enum class GameState { RUNNING, EXIT };

const int CELL_SIZE = 12;

class MainGame : public CrossEngine::IGameScreen {
public:
    MainGame(CrossEngine::Window* window);
    ~MainGame();

    virtual int GetNextScreenIndex() const override;

    virtual int GetPreviousScreenIndex() const override;

    virtual void Build() override;

    virtual void Destroy() override;

    virtual void OnEntry() override;

    virtual void OnExit() override;

    virtual void Update() override;

    virtual void Draw() override;


private:
    void init();
    void initRenderers();
    void initBalls();
    void update(float deltaTime);
    void drawHud();
    void processInput();

    int m_screenWidth = 0;
    int m_screenHeight = 0;

    std::vector<Ball> m_balls; ///< All the balls
    std::unique_ptr<Grid> m_grid; ///< Grid for spatial partitioning for collision

    int m_currentRenderer = 0;
    std::vector<BallRenderer*> m_ballRenderers;

    BallController m_ballController; ///< Controls balls

    CrossEngine::Window m_window; ///< The main window
    CrossEngine::SpriteBatch m_spriteBatch; ///< Renders all the balls
    CrossEngine::Camera2D m_camera; ///< Renders the scene
    CrossEngine::InputManager m_inputManager; ///< Handles input
    //CrossEngine::GLSLProgram m_textureProgram; ///< Shader for textures

    CrossEngine::FpsLimiter m_fpsLimiter; ///< Limits and calculates fps
    float m_fps = 0.0f;

    GameState m_gameState = GameState::RUNNING; ///< The state of the game
};

