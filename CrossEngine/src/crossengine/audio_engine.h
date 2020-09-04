/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_AUDIOENGINE_H_
#define CROSSENGINE_AUDIOENGINE_H_

#include <SDL/SDL_mixer.h>

#include <map>
#include <string>

namespace CrossEngine {
/**
 * @brief Control a audio file.
 */
class SoundEffect {
 public:
  friend class AudioEngine;

  /**
   * @brief Plays the effect file.
   *
   * @param[in] loops If loops == -1, loops forever
   *                  otherwise play it loops+1 times.
   */
  void Play(int loops = 0);

 private:
  Mix_Chunk* chunk_ = nullptr;
};

/**
 * @brief Control a song file.
 */
class Music {
 public:
  friend class AudioEngine;

  /**
   * @brief Construct a new Music object.
   */
  Music();

  /**
   * @brief Play the music file.
   *
   * @param[in] loops If loops == -1, loops forever
   *   otherwise play it loops times.
   */
  void Play(int loops = 1);

  /**
   * @brief Pauses whatever song is currently playing.
   */
  static void Pause();

  /**
   * @brief Stops whatever song is currently playing.
   */
  static void Stop();

  /**
   * @brief Resumes whatever song is currently playing.
   */
  static void Resume();

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
   */
  void Init();

  /**
   * @brief Destroy the audio engine
   */
  void Destroy();

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
  std::map<std::string, Mix_Chunk*> effect_map_;
  std::map<std::string, Mix_Music*> music_map_;

  bool is_initialized_;
};
}  // namespace CrossEngine

#endif  // CROSSENGINE_AUDIOENGINE_H_
