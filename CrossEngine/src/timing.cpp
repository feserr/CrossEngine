/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "crossengine/timing.h"

#include <SDL/SDL.h>

namespace CrossEngine {

FpsLimiter::FpsLimiter() {}
void FpsLimiter::Init(float max_fps) { SetMaxFPS(max_fps); }

void FpsLimiter::SetMaxFPS(float max_fps) { max_fps_ = max_fps; }

void FpsLimiter::Begin() { start_ticks_ = SDL_GetTicks(); }

float FpsLimiter::End() {
  CalculateFPS();

  float frameTicks = static_cast<float>(SDL_GetTicks() - start_ticks_);
  // Limit the FPS to the max FPS
  if (1000.0f / max_fps_ > frameTicks) {
    SDL_Delay((Uint32)(1000.0f / max_fps_ - frameTicks));
  }

  return fps_;
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
  frame_time_ = static_cast<float>(currentTicks - prevTicks);
  frameTimes[currentFrame % NUM_SAMPLES] = frame_time_;

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
    fps_ = 1000.0f / frameTimeAverage;
  } else {
    fps_ = 60.0f;
  }
}
}  // namespace CrossEngine
