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

#include "CrossEngine/Timing.h"

#include <SDL/SDL.h>

namespace CrossEngine {

    FpsLimiter::FpsLimiter() {
    }
    void FpsLimiter::Init(float maxFPS) {
        SetMaxFPS(maxFPS);
    }

    void FpsLimiter::SetMaxFPS(float maxFPS) {
        m_maxFPS = maxFPS;
    }

    void FpsLimiter::Begin() {
        m_startTicks = SDL_GetTicks();
    }

    float FpsLimiter::End() {
        CalculateFPS();

        float frameTicks = static_cast<float>(SDL_GetTicks() - m_startTicks);
        // Limit the FPS to the max FPS
        if (1000.0f / m_maxFPS > frameTicks) {
            SDL_Delay((Uint32)(1000.0f / m_maxFPS - frameTicks));
        }

        return m_fps;
    }

    void FpsLimiter::CalculateFPS() {
        // The number of frames to average
        static const int NUM_SAMPLES = 10;
        // Stores all the frametimes for each frame that we will average
        static float frameTimes[NUM_SAMPLES];
        // The current frame we are on
        static int currentFrame = 0;
        // The ticks of the previous frame
        static Uint32 prevTicks = SDL_GetTicks();

        // Ticks for the current frame
        Uint32 currentTicks = SDL_GetTicks();

        // Calculate the number of ticks (ms) for this frame
        m_frameTime = static_cast<float>(currentTicks - prevTicks);
        frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;

        // current ticks is now previous ticks
        prevTicks = currentTicks;

        // The number of frames to average
        int count;

        currentFrame++;
        if (currentFrame < NUM_SAMPLES) {
            count = currentFrame;
        } else {
            count = NUM_SAMPLES;
        }

        // Average all the frame times
        float frameTimeAverage = 0;
        for (int i = 0; i < count; i++) {
            frameTimeAverage += frameTimes[i];
        }
        frameTimeAverage /= count;

        // Calculate FPS
        if (frameTimeAverage > 0) {
            m_fps = 1000.0f / frameTimeAverage;
        } else {
            m_fps = 60.0f;
        }
    }
}  // namespace CrossEngine
