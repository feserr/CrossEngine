/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_AUDIOENGINE_H_
#define CROSSENGINE_AUDIOENGINE_H_

#include <SDL/SDL_mixer.h>

#include <string>
#include <unordered_map>

#include "error_manager.h"

namespace CrossEngine {
/**
 * @brief Control a audio file.
 */
class SoundEffect {
 public:
  /**
   * @brief Construct a new SoundEffect object.
   */
  SoundEffect();

  /**
   * @brief Construct a new SoundEffect object
   *
   * @param chunk The chunk effect.
   */
  explicit SoundEffect(Mix_Chunk* chunk);

  /**
   * @brief Set the Chunk object.
   *
   * @param chunk The chunk effect.
   */
  void SetChunk(Mix_Chunk* chunk) { chunk_ = chunk; }

  /**
   * @brief Plays the effect file.
   *
   * @param[in] loops If loops == -1, loops forever
   *                  otherwise play it loops+1 times.
   * @return Result OK if success, otherwise an error code.
   */
  Result Play(int loops = 0);

 private:
  Mix_Chunk* chunk_;
};

/**
 * @brief Control a song file.
 */
class Music {
 public:
  /**
   * @brief Construct a new Music object.
   */
  Music();

  /**
   * @brief Construct a new Music object.
   *
   * @param music The music.
   */
  explicit Music(Mix_Music* music);

  /**
   * @brief Set the Music object.
   *
   * @param music The music.
   */
  void SetMusic(Mix_Music* music) { music_ = music; }

  /**
   * @brief Play the music file.
   *
   * @param[in] loops If loops == -1, loops forever
   *   otherwise play it loops times.
   * @return Result OK if success, otherwise an error code.
   */
  Result Play(int loops = 1);

  /**
   * @brief Pauses whatever song is currently playing.
   *
   * @return Result OK if success, otherwise an error code.
   */
  Result Pause();

  /**
   * @brief Stops whatever song is currently playing.
   *
   * @return Result OK if success, otherwise an error code.
   */
  Result Stop();

  /**
   * @brief Resumes whatever song is currently playing.
   *
   * @return Result OK if success, otherwise an error code.
   */
  Result Resume();

 private:
  Mix_Music* music_;
};

/// Create and load a song or sound file
class AudioEngine {
 public:
  /**
   * @brief Construct a new audio engine object.
   */
  AudioEngine();

  /**
   * @brief Destroy the audio engine object.
   */
  ~AudioEngine();

  /**
   * @brief Initialize the audio engine.
   *
   * @return Result OK if success, otherwise an error code.
   */
  Result Init();

  /**
   * @brief Destroy the audio engine
   *
   * @return Result OK if success, otherwise an error code.
   */
  Result Destroy();

  /**
   * @brief Loads and map a sound file
   *
   * @param[in] file_path The file path
   * @return A SoundEffect object
   */

  SoundEffect LoadSoundEffect(const std::string& file_path);

  /**
   * @brief Loads a music.
   *
   * @param[in] file_path The file path.
   * @return A Music object.
   */
  Music LoadMusic(const std::string& file_path);

 private:
  std::unordered_map<std::string, Mix_Chunk*> effect_map_;
  std::unordered_map<std::string, Mix_Music*> music_map_;

  bool is_initialized_;
};
}  // namespace CrossEngine

#endif  // CROSSENGINE_AUDIOENGINE_H_
