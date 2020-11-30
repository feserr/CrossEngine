cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(CrossEngineRoot DESCRIPTION "Cross Engine")

enable_testing()
include(CTest)
add_subdirectory(google_unittests)

add_subdirectory(CrossEngine)
