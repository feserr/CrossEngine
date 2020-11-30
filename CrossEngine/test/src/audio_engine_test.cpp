/*
 * Copyright 2020 Javier Jorge. All rights reserved.
 * License: https://github.com/JJorgeDSIC/CppDecoder#license
 */

#include <crossengine/audio_engine.h>
#include <crossengine/error_manager.h>

#include <stdexcept>
#include <vector>

#include "gtest/gtest.h"

TEST(Init, AudioEngineTest) {
  CrossEngine::AudioEngine audioEngine;
  EXPECT_NO_THROW(audioEngine.Init());
  EXPECT_EQ(audioEngine.Destroy(), CrossEngine::Result::OK);
}

TEST(InitTwice, AudioEngineTest) {
  CrossEngine::AudioEngine audioEngine;
  EXPECT_NO_THROW(audioEngine.Init());
  ASSERT_THROW(audioEngine.Init(), std::runtime_error);
}

TEST(LoadEffect, AudioEngineTest) {
  CrossEngine::AudioEngine audioEngine;
  EXPECT_NO_THROW(audioEngine.Init());
  EXPECT_NO_THROW(audioEngine.LoadSoundEffect("./assets/effects/pistol.wav"));
  EXPECT_EQ(audioEngine.Destroy(), CrossEngine::Result::OK);
}

TEST(LoadWrongEffect, AudioEngineTest) {
  CrossEngine::AudioEngine audioEngine;
  EXPECT_NO_THROW(audioEngine.Init());
  ASSERT_THROW(audioEngine.LoadSoundEffect(""), std::runtime_error);
}

TEST(PlayEffect, AudioEngineTest) {
  CrossEngine::AudioEngine audioEngine;
  EXPECT_NO_THROW(audioEngine.Init());
  CrossEngine::SoundEffect effect =
      audioEngine.LoadSoundEffect("./assets/effects/pistol.wav");
  EXPECT_EQ(effect.Play(), CrossEngine::Result::OK);
  EXPECT_EQ(audioEngine.Destroy(), CrossEngine::Result::OK);
}

TEST(LoadMusic, AudioEngineTest) {
  CrossEngine::AudioEngine audioEngine;
  EXPECT_NO_THROW(audioEngine.Init());
  EXPECT_NO_THROW(audioEngine.LoadMusic("./assets/music/XYZ.ogg"));
  EXPECT_EQ(audioEngine.Destroy(), CrossEngine::Result::OK);
}

TEST(LoadWrongMusic, AudioEngineTest) {
  CrossEngine::AudioEngine audioEngine;
  EXPECT_NO_THROW(audioEngine.Init());
  ASSERT_THROW(audioEngine.LoadMusic(""), std::runtime_error);
}

TEST(PlayMusic, AudioEngineTest) {
  CrossEngine::AudioEngine audioEngine;
  EXPECT_NO_THROW(audioEngine.Init());
  CrossEngine::Music music =
      audioEngine.LoadMusic("./assets/music/XYZ.ogg");
  EXPECT_EQ(music.Play(), CrossEngine::Result::OK);
  EXPECT_EQ(audioEngine.Destroy(), CrossEngine::Result::OK);
}

TEST(PlayMusicNegativeLoop, AudioEngineTest) {
  CrossEngine::AudioEngine audioEngine;
  EXPECT_NO_THROW(audioEngine.Init());
  CrossEngine::Music music =
      audioEngine.LoadMusic("./assets/music/XYZ.ogg");
  EXPECT_EQ(music.Play(-100), CrossEngine::Result::FAIL);
  EXPECT_EQ(audioEngine.Destroy(), CrossEngine::Result::OK);
}

TEST(PauseMusic, AudioEngineTest) {
  CrossEngine::AudioEngine audioEngine;
  EXPECT_NO_THROW(audioEngine.Init());
  CrossEngine::Music music =
      audioEngine.LoadMusic("./assets/music/XYZ.ogg");
  EXPECT_EQ(music.Play(), CrossEngine::Result::OK);
  EXPECT_EQ(music.Pause(), CrossEngine::Result::OK);
  EXPECT_EQ(audioEngine.Destroy(), CrossEngine::Result::OK);
}

TEST(StopMusic, AudioEngineTest) {
  CrossEngine::AudioEngine audioEngine;
  EXPECT_NO_THROW(audioEngine.Init());
  CrossEngine::Music music =
      audioEngine.LoadMusic("./assets/music/XYZ.ogg");
  EXPECT_EQ(music.Play(), CrossEngine::Result::OK);
  EXPECT_EQ(music.Pause(), CrossEngine::Result::OK);
  EXPECT_EQ(music.Stop(), CrossEngine::Result::OK);
  EXPECT_EQ(audioEngine.Destroy(), CrossEngine::Result::OK);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
