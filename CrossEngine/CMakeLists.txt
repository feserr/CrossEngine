cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

set(NAME crossengine)
set(REPO_VERSION 0.1.2)

project(${NAME} VERSION ${REPO_VERSION} DESCRIPTION "Cross Engine")

add_subdirectory(test)
