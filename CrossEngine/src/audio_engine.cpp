/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "crossengine/audio_engine.h"

#include <string>

namespace CrossEngine {
SoundEffect::SoundEffect() : chunk_() {}

SoundEffect::SoundEffect(Mix_Chunk* chunk) : chunk_(chunk) {}

Result SoundEffect::Play(int loops /* = 0 */) {
  if (Mix_PlayChannel(-1, chunk_, loops) == -1) {
    if (Mix_PlayChannel(0, chunk_, loops) == -1) {
      FatalError("Mix_PlayChannel error: " + std::string(Mix_GetError()));
    }
  }

  return Result::OK;
}

Music::Music() : music_() {}

Music::Music(Mix_Music* music) : music_(music) {}

Result Music::Play(int loops) {
  if (loops < -1) return Result::FAIL;
  Mix_PlayMusic(music_, loops);
  return Result::OK;
}

Result Music::Pause() {
  Mix_PauseMusic();
  return Result::OK;
}

Result Music::Stop() {
  Mix_HaltMusic();
  return Result::OK;
}

Result Music::Resume() {
  Mix_ResumeMusic();
  return Result::OK;
}

AudioEngine::AudioEngine() : is_initialized_(false) {}

AudioEngine::~AudioEngine() { Destroy(); }

Result AudioEngine::Init() {
  if (is_initialized_) {  // If it is already initialize
    FatalError("Tried to initialize Audio Engine twice!\n");
  }

  // Parameter can be a bitwise combination of MIX_INIT_FAC,
  // MIX_INIT_MOD, MIX_INIT_MP3, MIX_INIT_OGG
  if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1) {
    FatalError("Mix_Init error: " + std::string(Mix_GetError()));
  }

  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
    FatalError("Mix_OpenAudio error: " + std::string(Mix_GetError()));
  }

  is_initialized_ = true;

  return Result::OK;
}

Result AudioEngine::Destroy() {
  if (!is_initialized_) return Result::OK;

  is_initialized_ = false;

  for (auto& it : effect_map_) {  // Iterate all the effects
    Mix_FreeChunk(it.second);
  }

  for (auto& it : music_map_) {  // Iterate all the musics
    Mix_FreeMusic(it.second);
  }

  effect_map_.clear();
  music_map_.clear();

  Mix_CloseAudio();
  Mix_Quit();

  return Result::OK;
}

SoundEffect AudioEngine::LoadSoundEffect(const std::string& file_path) {
  // Try to find the audio in the cache
  auto it = effect_map_.find(file_path);

  SoundEffect effect;

  if (it == effect_map_.end()) {
    // Failed to find it, must load
    Mix_Chunk* chunk = Mix_LoadWAV(file_path.c_str());
    // Check for errors
    if (chunk == nullptr) {
      FatalError("Mix_LoadWAV error: " + std::string(Mix_GetError()));
    }

    effect.SetChunk(chunk);
    effect_map_[file_path] = chunk;

  } else {
    // Its already cached
    effect.SetChunk(it->second);
  }

  return effect;
}

Music AudioEngine::LoadMusic(const std::string& file_path) {
  // Try to find the audio in the cache
  auto it = music_map_.find(file_path);

  Music music;

  if (it == music_map_.end()) {
    // Failed to find it, must load
    Mix_Music* mixMusic = Mix_LoadMUS(file_path.c_str());
    // Check for errors
    if (mixMusic == nullptr) {
      FatalError("Mix_LoadMUS error: " + std::string(Mix_GetError()));
    }

    music.SetMusic(mixMusic);
    music_map_[file_path] = mixMusic;

  } else {
    // Its already cached
    music.SetMusic(it->second);
  }

  return music;
}
}  // namespace CrossEngine
