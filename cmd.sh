#!/bin/bash

BASEDIR=$(dirname "$0")
echo "$BASEDIR"

cd $BASEDIR

CMAKE_BINARY_DIR=$BASEDIR/build

#CONAN_COMPILER=gcc
#CONAN_COMPILER_VERSION=4.8

#CONAN_COMPILER=clang
#CONAN_COMPILER_VERSION=3.5

clean() {
    rm -Rf $CMAKE_BINARY_DIR
}

prep() {
    if [ ! -d "$CMAKE_BINARY_DIR" ]; then # Ensure target exists
        mkdir -p $CMAKE_BINARY_DIR
    fi
}

deps_get() {
    prep
    cd $CMAKE_BINARY_DIR && conan install .. --build missing && cd $BASEDIR
}

case $1 in
    deps.get)
        deps_get
        ;;
    debug.build)
        prep
        cd $CMAKE_BINARY_DIR && cmake .. -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles" && cd $BASEDIR
        ;;
    debug.release)
        cd $CMAKE_BINARY_DIR && make && cd $BASEDIR
        ;;
    prod.build)
        prep
        cd $CMAKE_BINARY_DIR && cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release && cd $BASEDIR
        ;;
    prod.release)
        cd $CMAKE_BINARY_DIR && make && cd $BASEDIR
        ;;
    clean)
        clean
        ;;
    esac
exit 0
