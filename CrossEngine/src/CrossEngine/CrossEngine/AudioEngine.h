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
