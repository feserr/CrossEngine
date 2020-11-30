cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/sdl2)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test/")

set(TEST_ASSETS_DIR ${CMAKE_BINARY_DIR}/test/assets)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/assets/effects/pistol.wav ${TEST_ASSETS_DIR}/effects/pistol.wav COPYONLY)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/assets/music/XYZ.ogg ${TEST_ASSETS_DIR}/music/XYZ.ogg COPYONLY)

find_library(CrossEngine_LIBRARY
  NAMES crossengine crossengineDebug crossengineRelease
  HINTS "${CMAKE_CURRENT_SOURCE_DIR}/../build/osx64_clang/bin/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../build/osx64_gcc/bin/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../build/linux64_clang/bin/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../build/linux64_gcc/bin/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../build/win64_vs2017/bin/"
)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

set(UNITTEST src/audio_engine_test.cpp)
set(LIB
  ${CrossEngine_LIBRARY}
  SDL2::Core
  SDL2::Mixer)
set(LIB_INCLUDE
  "../src/"
  "../deps/include"
  )

BUILD_UNIT_TEST(TEST_SRC ${UNITTEST} LIBS ${LIB} LIBS_INCLUDE ${LIB_INCLUDE})
