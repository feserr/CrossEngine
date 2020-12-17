cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/sdl2)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test/")

set(TEST_ASSETS_DIR ${CMAKE_BINARY_DIR}/test/assets)

find_library(CrossEngine_LIBRARY
  NAMES crossengine crossengineDebug crossengineRelease
  HINTS "${CMAKE_CURRENT_SOURCE_DIR}/../build/osx64_clang/bin/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../build/osx64_gcc/bin/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../build/linux64_clang/bin/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../build/linux64_gcc/bin/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../build/win64_vs2017/bin/"
)

find_library(BGFX_LIBRARY
  NAMES bgfx bgfxDebug bgfxRelease
  HINTS "${CMAKE_CURRENT_SOURCE_DIR}/../build/osx64_clang/bin/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../build/osx64_gcc/bin/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../build/linux64_clang/bin/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../build/linux64_gcc/bin/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../build/win64_vs2017/bin/"
)

find_library(BX_LIBRARY
  NAMES bx bxDebug bxRelease
  HINTS "${CMAKE_CURRENT_SOURCE_DIR}/../build/osx64_clang/bin/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../build/osx64_gcc/bin/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../build/linux64_clang/bin/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../build/linux64_gcc/bin/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../build/win64_vs2017/bin/"
)

find_library(BIMG_LIBRARY
  NAMES bimg bimgDebug bimgRelease
  HINTS "${CMAKE_CURRENT_SOURCE_DIR}/../build/osx64_clang/bin/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../build/osx64_gcc/bin/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../build/linux64_clang/bin/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../build/linux64_gcc/bin/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../build/win64_vs2017/bin/"
)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

if( APPLE )
	find_library( COCOA_LIBRARY Cocoa )
	find_library( METAL_LIBRARY Metal )
	find_library( QUARTZCORE_LIBRARY QuartzCore )
	mark_as_advanced( COCOA_LIBRARY )
	mark_as_advanced( METAL_LIBRARY )
	mark_as_advanced( QUARTZCORE_LIBRARY )
endif()

if( UNIX AND NOT APPLE)
	find_package(X11 REQUIRED)
	find_package(OpenGL REQUIRED)
endif()

set(UNITTEST src/cross_engine_init_test.cpp)
set(LIB
  ${CrossEngine_LIBRARY}
  ${BGFX_LIBRARY}
  ${BX_LIBRARY}
  ${BIMG_LIBRARY}
  ${X11_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${COCOA_LIBRARY}
  ${METAL_LIBRARY}
  ${QUARTZCORE_LIBRARY}
  SDL2::Core
  SDL2::Mixer)
set(LIB_INCLUDE
  "../src/"
  "../deps/include"
  "../../external/bgfx/include"
  "../../external/bx/include"
  "../../external/bimg/include"
  )

BUILD_UNIT_TEST(TEST_SRC ${UNITTEST} LIBS ${LIB} LIBS_INCLUDE ${LIB_INCLUDE})
