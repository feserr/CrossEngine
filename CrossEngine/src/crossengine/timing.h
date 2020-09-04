/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_TIMING_H_
#define CROSSENGINE_TIMING_H_

namespace CrossEngine {
/// Calculates FPS and also limits FPS
class FpsLimiter {
 public:
  /**
   * @brief Construct a new FpsLimiter object.
   */
  FpsLimiter();

  /**
   * @brief Initializes the FPS limiter.
   * For now, this is analogous to setMaxFPS.
   *
   * @param[in] max_fps The maximun fps of the game.
   */
  void Init(float max_fps);

  /**
   * @brief Sets the desired max FPS.
   *
   * @param[in] max_fps The maximun fps of the game.
   */
  void SetMaxFPS(float max_fps);

  /**
   * @brief Start counting.
   */
  void Begin();

  /**
   * @brief Ends counting.
   *
   * @return float The current fps.
   */
  float End();

 private:
  /**
   * @brief Calculates the current FPS.
   */
  void CalculateFPS();

  float fps_;
  float max_fps_;
  float frame_time_;
  unsigned int start_ticks_;
};
}  // namespace CrossEngine

#endif  // CROSSENGINE_TIMING_H_
