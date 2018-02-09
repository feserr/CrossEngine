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
    return SCREEN_INDEX_NO_SCREEN;
}

int GameplayScreen::GetPreviousScreenIndex() const {
    return SCREEN_INDEX_MAINMENU;
}

void GameplayScreen::Build() {
}

void GameplayScreen::Destroy() {
    // Cleanup.
    if (bgfx::isValid(m_program) ) {
        bgfx::destroy(m_program);
    }

    bgfx::destroy(m_ibh);
    bgfx::destroy(m_vbh);
    bgfx::destroy(s_texColor);
}

void GameplayScreen::OnEntry() {
    // Initialize spritebatch
    m_spriteBatch.Init();

    // Init camera
    m_camera.Init(m_window->GetScreenWidth(), m_window->GetScreenHeight());
    m_camera.SetPosition(glm::vec2(m_window->GetScreenWidth() / 2.0f,
        m_window->GetScreenHeight() / 2.0f));
    m_camera.SetScale(1.0f);

    // Init players
    //glm::vec2 position(32.0f, m_window->GetScreenHeight() / 2);
    glm::vec2 position(1.9f, 1.0f);
    glm::vec2 drawDims(32.0f, 32.0f);
    glm::vec2 collisionDims(32.0f, 48.0f);
    m_playerOne.Init(position, drawDims, collisionDims,
        CrossEngine::ColorRGBA8(255, 255, 255, 255), PlayerType::PLAYERONE);

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

        int t_goal = 0;
        //int t_goal = m_ball.Update(deltaTime, m_windowSize);
        m_playerOne.Update(deltaTime, m_game->inputManager, m_windowSize);

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

    m_camera.Update();
}

void GameplayScreen::Draw() {
    float at[3] = { 0.0f, 0.0f, 0.0f };
    float eye[3] = { 0.0f, 0.0f, -5.0f };

    float view[16];
    float proj[16];
    bx::mtxLookAt(view, eye, at);

    // Set view and projection matrix for view 1.
    const float aspectRatio = float(m_window->GetScreenHeight()) /
        float(m_window->GetScreenWidth());
    const float size = 1000.0f;
    const bgfx::Caps* caps = bgfx::getCaps();
    bx::mtxOrtho(proj, -size, size, size*aspectRatio, -size*aspectRatio, 0.0f,
         1000.0f, 0.0f, caps->homogeneousDepth);

    // Set view and projection matrix for view 0.
    bgfx::setViewTransform(0, view, proj);

    m_spriteBatch.Begin();

    m_playerOne.Draw(m_spriteBatch);

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
