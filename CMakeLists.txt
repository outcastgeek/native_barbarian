project(FoundationTimer)
cmake_minimum_required(VERSION 2.8.12)

#cmake -G "Unix Makefiles" .
#set(CMAKE_GENERATOR "Unix Makefiles")
message("generator is set to ${CMAKE_GENERATOR}")

set(CMAKE_VERBOSE_MAKEFILE TRUE)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)

#set(CMAKE_CXX_COMPILER g++-6)
#set(CMAKE_C_COMPILER gcc-6)

#set(CMAKE_CXX_COMPILER /usr/local/bin/g++-6)
#set(CMAKE_C_COMPILER /usr/local/bin/gcc-6)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")

execute_process(COMMAND conan install .. --build missing)
#
#if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake) #Clion, with conanbuildinfo.cmake in build folder
#    include(${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake)
#else()
#    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake) # Not CLion
#endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/conanbuildinfo.cmake) #Clion, with conanbuildinfo.cmake in #CMAKE_CURRENT_SOURCE_DIR folder
    include(${CMAKE_CURRENT_SOURCE_DIR}/conanbuildinfo.cmake)
else()
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake) # Not CLion
endif()


conan_basic_setup()

add_executable(timer timer.cpp)
target_link_libraries(timer ${CONAN_LIBS})
