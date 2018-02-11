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

#ifndef _AUDIOENGINE_H_
#define _AUDIOENGINE_H_

#include <SDL/SDL_mixer.h>
#include <string>
#include <map>

namespace CrossEngine {
/// Control a audio file
class SoundEffect {
 public:
    friend class AudioEngine;

    /**
     * \brief      Plays the effect file.
     *
     * \param[in]  loops  If loops == -1, loops forever
     *                    otherwise play it loops+1 times
     */
    void Play(int loops = 0);

 private:
    Mix_Chunk* m_chunk = nullptr;
};

/// Control a song file
class Music {
 public:
    friend class AudioEngine;

    /**
     * \brief      Play the music file
     *
     * \param[in]  loops  If loops == -1, loops forever
     *                    otherwise play it loops times
     */
    void Play(int loops = 1);

    /// Pauses whatever song is currently playing
    static void Pause();
    /// Stops whatever song is currently playing
    static void Stop();
    /// Resumes whatever song is currently playing
    static void Resume();

 private:
    Mix_Music* m_music = nullptr;
};

/// Create and load a song or sound file
class AudioEngine {
 public:
    /// Default constructor
    AudioEngine();
    /// Default destructor
    ~AudioEngine();

    /// Initialize the audio engine
    void Init();
    /// Destroy the audio engine
    void Destroy();
    
    /**
     * \brief      Loads and map a sound file
     *
     * \param[in]  filePath  The file path
     *
     * \return     A SoundEffect object
     */
    SoundEffect LoadSoundEffect(const std::string& filePath);

    /**
     * \brief      Loads a music.
     *
     * \param[in]  filePath  The file path
     *
     * \return     A Music object
     */
    Music LoadMusic(const std::string& filePath);

 private:
    std::map<std::string, Mix_Chunk*> m_effectMap;  ///< Effects cache
    std::map<std::string, Mix_Music*> m_musicMap;  ///< Music cache

    bool m_isInitialized = false;
};
}  // namespace CrossEngine

#endif  // _AUDIOENGINE_H_
