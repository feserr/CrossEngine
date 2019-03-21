/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "GameplayScreen.h"
#include "ScreenIndexs.h"

#include <SDL/SDL.h>
#include <CrossEngine/IMainGame.h>
#include <CrossEngine/ResourceManager.h>
#include <iostream>
#include <random>

const float DESIRED_FPS = 60.0f; // FPS the game is designed to run at
const int MAX_PHYSICS_STEPS = 6; // Max number of physics steps per frame
const float MS_PER_SECOND = 1000; // Number of milliseconds in a second
const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS; // The desired frame time per frame
const float MAX_DELTA_TIME = 1.0f; // Maximum size of deltaTime

GameplayScreen::GameplayScreen(CrossEngine::Window* window) : m_window(window){
    m_screenIndex = SCREEN_INDEX_GAMEPLAY;
}

GameplayScreen::~GameplayScreen() {

}

int GameplayScreen::GetNextScreenIndex() const {
    return SCREEN_INDEX_MAINMENU;
}

int GameplayScreen::GetPreviousScreenIndex() const {
    return SCREEN_INDEX_MAINMENU;
}

void GameplayScreen::Build() {
}

void GameplayScreen::Destroy() {
    // Cleanup.
}

void GameplayScreen::OnEntry() {
    // Initialize spritebatch
    m_spriteBatch.Init();

    // Init camera
    m_camera.Init(m_window->GetScreenWidth(), m_window->GetScreenHeight());
    m_camera.SetPosition(glm::vec2(0.0f));
    m_camera.SetScale(1.0f);

    // Init players
    glm::vec2 position(32.0f, m_window->GetScreenHeight() / 2);
    glm::vec2 drawDims(32.0f, 32.0f);
    glm::vec2 collisionDims(32.0f, 48.0f);
    m_playerOne.Init(position, drawDims, collisionDims,
        CrossEngine::ColorRGBA8(255, 255, 255, 255), PlayerType::PLAYERONE);

    position = glm::vec2(m_window->GetScreenWidth() - 32.0f,
                         m_window->GetScreenHeight() / 2);
    m_playerTwo.Init(position, drawDims, collisionDims,
        CrossEngine::ColorRGBA8(255, 255, 255, 255), PlayerType::PLAYERTWO);

    // Init the ball
    position = glm::vec2(m_window->GetScreenWidth() / 2,
                         m_window->GetScreenHeight() / 2);
    glm::vec2 vel(-6.0f, 0.0f);
    m_ball.Init(8.0f, 0.0f, position, vel);

    // Init the environment
    position = glm::vec2(m_window->GetScreenWidth() / 2, 0.0f);
    for(int i = 16; i <= m_window->GetScreenHeight(); i += 64) {
        Environment environment;
        position.y = i;
        environment.Init(position, drawDims,
            CrossEngine::ColorRGBA8(255, 255, 255, 130));
        m_enviroment.push_back(environment);
    }

    m_windowSize = glm::vec2(m_window->GetScreenWidth(),
        m_window->GetScreenHeight());
}

void GameplayScreen::OnExit() {
}

void GameplayScreen::Update() {
    //checkInput();

    // Calculate the frameTime in milliseconds
    static Uint32 previousTicks = SDL_GetTicks();
    Uint32 newTicks = SDL_GetTicks();
    Uint32 frameTime = newTicks - previousTicks;
    previousTicks = newTicks;
    // Get the total delta time
    float totalDeltaTime = (float)frameTime / DESIRED_FRAMETIME;

    int i = 0;
    int goal = 0;
    while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS) {
        // The deltaTime should be the the smaller of the totalDeltaTime and
        // MAX_DELTA_TIME
        float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
        // Update all physics here and pass in deltaTime

        int t_goal = m_ball.Update(deltaTime, m_windowSize);
        m_playerOne.Update(deltaTime, m_game->inputManager, m_windowSize,
            m_ball);
        m_playerTwo.Update(deltaTime, m_game->inputManager, m_windowSize,
            m_ball);

        // Since we just took a step that is length deltaTime, subtract from
        // totalDeltaTime
        totalDeltaTime -= deltaTime;
        ++i;

        // Prevent scoring more than one goal
        if (goal == 0) {
            goal = t_goal;
        }
    }

    if (goal == 1) {
        ++m_iScorePlayerTwo;
        //m_scorePlayerTwo->setText(std::to_string(m_iScorePlayerTwo));
    } else if (goal == 2) {
        ++m_iScorePlayerOne;
        //m_scorePlayerOne->setText(std::to_string(m_iScorePlayerOne));
    }

    glm::vec2 cp = m_camera.GetPosition();
    cp.x--;
    m_camera.SetPosition(cp);
    m_camera.Update();
}

void GameplayScreen::Draw() {
    m_camera.Draw();

    m_spriteBatch.Begin();

    m_playerOne.Draw(m_spriteBatch);
    m_playerTwo.Draw(m_spriteBatch);
    m_ball.Draw(m_spriteBatch);

    for(Environment environment : m_enviroment) {
        environment.Draw(m_spriteBatch);
    }

    m_spriteBatch.End();
    m_spriteBatch.RenderBatch();
}

void GameplayScreen::initUI() {
    // Init the UI
}

void GameplayScreen::checkInput() {
    SDL_Event evnt;
    while (SDL_WaitEvent(&evnt)) {
        m_game->OnSDLEvent(evnt);
        switch (evnt.type) {
            case SDL_QUIT:
                onExitClicked();
                break;
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                break;
        }
    }
}

bool GameplayScreen::onExitClicked() {
    m_currentState = CrossEngine::ScreenState::EXIT_APPLICATION;
    return true;
}
