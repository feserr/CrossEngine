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

#ifndef _IGAMESCREEN_H_
#define _IGAMESCREEN_H_

const int SCREEN_INDEX_NO_SCREEN = -1;

namespace CrossEngine {
/// Main game interface
class IMainGame;

enum class ScreenState {
    NONE,
    RUNNING,
    EXIT_APPLICATION,
    CHANGE_NEXT,
    CHANGE_PREVIOUS
};

/// Game screen interface
class IGameScreen {
 public:
    friend class ScreenList;

    /// Default constructor
    IGameScreen() {
    }

    /// Default destructor
    virtual ~IGameScreen() {
    }

    /**
     * \brief      Gets the next screen index.
     *
     * \return     The next screen index.
     */
    virtual int GetNextScreenIndex() const = 0;

    /**
     * \brief      Gets the previous screen index.
     *
     * \return     The previous screen index.
     */
    virtual int GetPreviousScreenIndex() const = 0;

    /// Builds the game.
    virtual void Build() = 0;

    /// Destroy the game.
    virtual void Destroy() = 0;

    /// Called when a screen enters focus
    virtual void OnEntry() = 0;

    /// Called when a screen exits focus.
    virtual void OnExit() = 0;

    /// Updates the game screen.
    virtual void Update() = 0;

    /// Draw the game screen.
    virtual void Draw() = 0;

    /**
     * \brief      Gets the screen index.
     *
     * \return     The screen index.
     */
    int GetScreenIndex() const { return m_screenIndex; }

    /// Sets the running.
    void SetRunning() { m_currentState = ScreenState::RUNNING; }

    /**
     * \brief      Gets the state.
     *
     * \return     The state.
     */
    ScreenState GetState() const { return m_currentState; }

    /**
     * \brief      Sets the parent game.
     *
     * \param      game  The game
     */
    void SetParentGame(IMainGame* game) { m_game = game; }

 protected:
    ScreenState m_currentState = ScreenState::NONE;
    IMainGame* m_game = nullptr;
    int m_screenIndex = -1;
};
}  // namespace CrossEngine

#endif  // _IGAMESCREEN_H_
