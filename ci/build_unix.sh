#!/bin/bash

workspace=`pwd`

chmod +x ${workspace}/external/bx/tools/bin/${OS_NAME}/genie
cd CrossEngine
${workspace}/external/bx/tools/bin/${OS_NAME}/genie --gcc=${GENIE_COMPILER} gmake
make -C build/projects/gmake-${TRAVIS_OS_NAME} -j3 config=${BUILD_TYPE} all
cd BallGame
${workspace}/external/bx/tools/bin/${OS_NAME}/genie --gcc=${GENIE_COMPILER} gmake
make -C build/projects/gmake-${TRAVIS_OS_NAME} -j3 config=${BUILD_TYPE} all
cd ${workspace}
cd Pong
${workspace}/external/bx/tools/bin/${OS_NAME}/genie --gcc=${GENIE_COMPILER} gmake
make -C build/projects/gmake-${TRAVIS_OS_NAME} -j3 config=${BUILD_TYPE} all
cd ${workspace}