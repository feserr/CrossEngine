/*
    Copyright 2017-2018 Elías Serrano. All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY COPYRIGHT HOLDER ``AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
    PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER OR
    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
    OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "CrossEngine/AudioEngine.h"
#include "CrossEngine/CrossErrors.h"

#include <string>

namespace CrossEngine {
    void SoundEffect::Play(int loops /* = 0 */ ) {
        if (Mix_PlayChannel(-1, m_chunk, loops) == -1) {
            if (Mix_PlayChannel(0, m_chunk, loops) == -1) {
                FatalError("Mix_PlayChannel error: " +
                    std::string(Mix_GetError()));
            }
        }
    }

    void Music::Play(int loops /* = -1 */) {
        Mix_PlayMusic(m_music, loops);
    }

    void Music::Pause() {
        Mix_PauseMusic();
    }

    void Music::Stop() {
        Mix_HaltMusic();
    }

    void Music::Resume() {
        Mix_ResumeMusic();
    }

    AudioEngine::AudioEngine() {
        // Empty
    }

    AudioEngine::~AudioEngine() {
        Destroy();
    }


    void AudioEngine::Init() {
        if (m_isInitialized) {  // If it is already initialize
            FatalError("Tried to initialize Audio Engine twice!\n");
        }

        // Parameter can be a bitwise combination of MIX_INIT_FAC,
        // MIX_INIT_MOD, MIX_INIT_MP3, MIX_INIT_OGG
        if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1) {
            FatalError("Mix_Init error: " + std::string(Mix_GetError()));
        }

        if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024)
            == -1) {
            FatalError("Mix_OpenAudio error: " + std::string(Mix_GetError()));
        }

        m_isInitialized = true;
    }

    void AudioEngine::Destroy() {
        if (m_isInitialized) {  // If it is initialized
            m_isInitialized = false;

            for (auto& it : m_effectMap) {  // Iterate all the effects
                Mix_FreeChunk(it.second);
            }

            for (auto& it : m_musicMap) {  // Iterate all the musics
                Mix_FreeMusic(it.second);
            }

            m_effectMap.clear();
            m_musicMap.clear();

            Mix_CloseAudio();
            Mix_Quit();
        }
    }

    SoundEffect AudioEngine::LoadSoundEffect(const std::string& filePath) {
        // Try to find the audio in the cache
        auto it = m_effectMap.find(filePath);

        SoundEffect effect;

        if (it == m_effectMap.end()) {
            // Failed to find it, must load
            Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
            // Check for errors
            if (chunk == nullptr) {
                FatalError("Mix_LoadWAV error: " + std::string(Mix_GetError()));
            }

            effect.m_chunk = chunk;
            m_effectMap[filePath] = chunk;

        } else {
            // Its already cached
            effect.m_chunk = it->second;
        }

        return effect;
    }

    Music AudioEngine::LoadMusic(const std::string& filePath) {
        // Try to find the audio in the cache
        auto it = m_musicMap.find(filePath);

        Music music;

        if (it == m_musicMap.end()) {
            // Failed to find it, must load
            Mix_Music* mixMusic = Mix_LoadMUS(filePath.c_str());
            // Check for errors
            if (mixMusic == nullptr) {
                FatalError("Mix_LoadMUS error: " + std::string(Mix_GetError()));
            }

            music.m_music = mixMusic;
            m_musicMap[filePath] = mixMusic;

        } else {
            // Its already cached
            music.m_music = it->second;
        }

        return music;
    }
}  // namespace CrossEngine
