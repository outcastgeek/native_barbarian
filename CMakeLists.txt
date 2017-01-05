project(FoundationTimer)
cmake_minimum_required(VERSION 2.8.12)

#cmake -G "Unix Makefiles" .
#set(CMAKE_GENERATOR "Unix Makefiles")
message("generator is set to ${CMAKE_GENERATOR}")

set(CMAKE_VERBOSE_MAKEFILE TRUE)

# set(CMAKE_CXX_COMPILER clang++)
# set(CMAKE_C_COMPILER clang)

#set(CMAKE_CXX_COMPILER g++-6)
#set(CMAKE_C_COMPILER gcc-6)

#set(CMAKE_CXX_COMPILER /usr/local/bin/g++-6)
#set(CMAKE_C_COMPILER /usr/local/bin/gcc-6)

#set(CONAN_COMPILER gcc)
#set(CONAN_COMPILER_VERSION 4.8)

#set(CONAN_COMPILER clang)
#set(CONAN_COMPILER_VERSION 8.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
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

add_subdirectory(proto)
#include_directories(${CMAKE_CURRENT_BINARY_DIR/proto})
include_directories(${CMAKE_BINARY_DIR}/proto)

#### BOOST
set(BOOST_SRC ${CMAKE_SOURCE_DIR}/src/boost)
add_executable(main_boost ${BOOST_SRC}/main_boost.cpp)
target_link_libraries(main_boost ${CONAN_LIBS})

#### POCO
set(POCO_SRC ${CMAKE_SOURCE_DIR}/src/poco)
add_executable(timer ${POCO_SRC}/timer.cpp)
target_link_libraries(timer ${CONAN_LIBS})

#### ZMQ
set(ZMQ_SRC ${CMAKE_SOURCE_DIR}/src/zmq)
add_executable(hello_zmq ${ZMQ_SRC}/hello_zmq.cpp)
target_link_libraries(hello_zmq ${CONAN_LIBS})

#### ZMQ_PROTO
set(ZMQ_PROTO_SRC ${CMAKE_SOURCE_DIR}/src/zmq_proto)
add_executable(zmq_proto_server ${ZMQ_PROTO_SRC}/server.cpp)
target_link_libraries(zmq_proto_server proto ${CONAN_LIBS})
add_executable(zmq_proto_client ${ZMQ_PROTO_SRC}/client.cpp)
target_link_libraries(zmq_proto_client proto ${CONAN_LIBS})
