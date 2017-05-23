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

#ifndef _TIMING_H_
#define _TIMING_H_

namespace CrossEngine {
/// Calculates FPS and also limits FPS
class FpsLimiter {
 public:
    FpsLimiter();

    /// Initializes the FPS limiter.
    // For now, this is analogous to setMaxFPS
    void Init(float maxFPS);

    /// Sets the desired max FPS
    void SetMaxFPS(float maxFPS);

    void Begin();

    /// Return the current FPS as a float
    float End();

 private:
    // Calculates the current FPS
    void CalculateFPS();

    // Variables
    float m_fps;
    float m_maxFPS;
    float m_frameTime;
    unsigned int m_startTicks;
};
}  // namespace CrossEngine

#endif  // _TIMING_H_
